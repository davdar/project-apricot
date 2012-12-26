module Main where

import qualified Graphics.UI.SDL as SDL
import qualified Graphics.UI.SDL.Image as SDL
import qualified Data.Map as Map
import Data.Map (Map)
import Data.Array
import Data.Array.MArray

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

data GameState = GameState 
  { gameStateWorld :: World
  , gameStatePlayers :: Map Int Player
  }

worldSize :: (Int,Int)
worldSize = (100, 100)

graphicsSize :: (Int,Int)
graphicsSize = (800, 600)

tileSize :: (Int,Int)
tileSize =
  let (ww,wh) = worldSize
      (gw,gh) = graphicsSize
  in (gw / ww, gh / wh)

scenarioOne :: IO GameState
scenarioOne = do
  grid <- newArray worldSize Open
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
  tileSurf <- SDL.load "froggy.png"
  eventLoop
  SDL.quit
  print "done"
  where
    eventLoop = do
      e <- SDL.waitEventBlocking
      checkEvent e
    checkEvent (SDL.KeyUp _) = return ()
    checkEvent _ = eventLoop
