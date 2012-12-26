module Main where

import Control.Monad
import Data.Array.IO
import Data.Array.MArray
import Data.IORef
import Data.Map (Map)
import System.IO.Unsafe
import qualified Data.Map as Map
import qualified Graphics.UI.SDL as SDL
import qualified Graphics.UI.SDL.Image as SDL
import Data.Functor

data Player = Player
  { playerId :: Int
  , playerHeroes :: [Int]
  , playerTowns :: [Int]
  }

data Hero = Hero
  { heroId :: Int
  , heroLoc :: (Int, Int)
  }

data Town = Town
  { townId :: Int
  , townLoc :: (Int,Int)
  }

data World = World
  { worldGrid :: IOArray (Int,Int) WorldObject
  }

data WorldObject =
    Open
  | Closed
  | HeroObject Int
  | TownObject Int
  deriving (Eq)

data GameState = GameState 
  { gameStateWorld :: World
  , gameStatePlayers :: Map Int Player
  }

worldSize :: (Int,Int)
worldSize = (100, 100)

graphicsSize :: (Int,Int)
graphicsSize = (960, 640)

tileSize :: (Int,Int)
tileSize = (32,32)

currentScreenPos :: IORef (Int,Int)
currentScreenPos = unsafePerformIO $ newIORef (0,0)
{-# NOINLINE currentScreenPos #-}

scenarioOne :: IO GameState
scenarioOne = do
  grid <- newArray ((0,0),worldSize) Open
  writeArray grid (5,5) Closed
  writeArray grid (5,6) Closed
  return $ GameState (World grid) Map.empty

main :: IO ()
main = do
  let (gw,gh) = graphicsSize 
  SDL.init [SDL.InitEverything]
  SDL.setVideoMode gw gh 32 []
  SDL.setCaption "Video Test!" "video test"
  mainSurf <- SDL.getVideoSurface
  tileSurf <- SDL.load "froggy_32x32.png"
  eventLoop mainSurf tileSurf
  SDL.quit
  where
    eventLoop mainSurf tileSurf = do
      draw mainSurf tileSurf
      e <- SDL.waitEventBlocking
      checkEvent e mainSurf tileSurf
    checkEvent (SDL.KeyUp (SDL.Keysym SDL.SDLK_RIGHT _ _)) mainSurf tileSurf = do
      modifyIORef currentScreenPos $ \ (x,y) -> (x+1,y)
      eventLoop mainSurf tileSurf
    checkEvent (SDL.KeyUp (SDL.Keysym SDL.SDLK_LEFT _ _)) mainSurf tileSurf = do
      modifyIORef currentScreenPos $ \ (x,y) -> (x,y+1)
      eventLoop mainSurf tileSurf
    checkEvent _ mainSurf tileSurf = eventLoop mainSurf tileSurf
    draw mainSurf tileSurf = do
      grid <- liftM (worldGrid . gameStateWorld) $ scenarioOne :: IO (IOArray (Int,Int) WorldObject)
      assocs <- getAssocs grid :: IO [((Int,Int),WorldObject)]
      (screenx,screeny) <- readIORef currentScreenPos
      SDL.fillRect mainSurf Nothing (SDL.Pixel 0)
      forM_ assocs $ \ ((x,y),e) ->
        when (e == Closed) $ do
          SDL.blitSurface tileSurf (Just (SDL.Rect 0 0 32 32)) mainSurf (Just (SDL.Rect (x*32 - screenx) (y*32 - screeny) 0 0))
          return ()
      SDL.flip mainSurf
