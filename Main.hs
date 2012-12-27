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

worldW = 100
worldH = 100
worldSize = (worldW,worldH)

graphicsW = 960
graphicsH = 640
graphicsSize = (graphicsW,graphicsH)

minScreenW = 0
minScreenH = 0
maxScreenW = worldW * tileW - graphicsW
maxScreenH = worldH * tileH - graphicsH

tileW = 32
tileH = 32
tileSize = (tileW,tileH)

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
  SDL.setVideoMode graphicsW graphicsH 32 []
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
        SDL.SDLK_LEFT -> scrollLeft
        SDL.SDLK_RIGHT -> scrollRight
        SDL.SDLK_UP -> scrollUp
        SDL.SDLK_DOWN -> scrollDown
        SDL.SDLK_q -> exit
        _ -> return ()
    SDL.MouseMotion x' y' _xdiff _ydiff -> do
      let (x,y) = (fromIntegral x', fromIntegral y')
      when (x < 20) scrollLeft
      when (x > graphicsW - 20) scrollRight
      when (y < 20) scrollUp
      when (y > graphicsH - 20) scrollDown
    _ -> print "yo"
  eventLoop
  where
    scrollLeft = modifyIORef currentScreenPos $ \ (x,y) -> (min (x+1) maxScreenW,y)
    scrollRight = modifyIORef currentScreenPos $ \ (x,y) -> (max (x-1) minScreenW,y)
    scrollUp = modifyIORef currentScreenPos $ \ (x,y) -> (x, min (y+1) maxScreenH)
    scrollDown = modifyIORef currentScreenPos $ \ (x,y) -> (x, max (y-1) minScreenH)
