module Main where

import Control.Monad
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
import Assets
import GameState
import System.Exit

currentScreenPos :: IORef (Int,Int)
currentScreenPos = unsafePerformIO $ newIORef (0,0)
{-# NOINLINE currentScreenPos #-}

worldSize :: (Int,Int)
worldSize = (100, 100)

graphicsSize :: (Int,Int)
graphicsSize = (960, 640)

tileSize :: (Int,Int)
tileSize = (32,32)

scenarioOne :: IO GameState
scenarioOne = do
  grid <- newArray ((0,0),worldSize) Open
  writeArray grid (5,5) Closed
  writeArray grid (5,6) Closed
  return $ GameState (World grid) Map.empty

mainDraw :: (SDL.Surface -> IO ()) -> IO ()
mainDraw action = do
  s <- SDL.getVideoSurface
  SDL.fillRect s Nothing (SDL.Pixel 0)
  action s
  SDL.flip s
  
main :: IO ()
main = do
  SDL.init [SDL.InitEverything]
  let (gw,gh) = graphicsSize 
  SDL.setVideoMode gw gh 32 []
  SDL.setCaption "Project Apricot" "apricot"
  loadAssets
  writeIORef gameState =<< scenarioOne
  eventLoop

exit :: IO ()
exit = do
  SDL.quit
  exitSuccess
  
eventLoop :: IO ()
eventLoop = do
  mainDraw $ \ s -> do
    grid <- getAssocs <=< liftM (worldGrid . gameStateWorld) $ readIORef gameState
    (screenx,screeny) <- readIORef currentScreenPos
    tile <- liftM assetsFroggy $ readIORef assets
    forM_ grid $ \ ((x,y),e) ->
      when (e == Closed) $ do
        SDL.blitSurface tile (Just (SDL.Rect 0 0 32 32)) 
                        s (Just (SDL.Rect (x*32 - screenx) (y*32 - screeny) 0 0))
        return ()
  checkEvent =<< SDL.waitEventBlocking

checkEvent :: SDL.Event -> IO ()
checkEvent e = do
  case e of
    SDL.KeyUp (SDL.Keysym k mod uni) ->
      case k of
        SDL.SDLK_LEFT -> modifyIORef currentScreenPos $ \ (x,y) -> (x-1,y)
        SDL.SDLK_RIGHT -> modifyIORef currentScreenPos $ \ (x,y) -> (x+1,y)
        SDL.SDLK_UP -> modifyIORef currentScreenPos $ \ (x,y) -> (x,y-1)
        SDL.SDLK_DOWN -> modifyIORef currentScreenPos $ \ (x,y) -> (x,y+1)
        SDL.SDLK_q -> exit
        _ -> return ()
    _ -> return ()
  eventLoop
