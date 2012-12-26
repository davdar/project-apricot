module Main where

import Control.Monad
import Data.IORef
import Graphics.UI.GLUT

main :: IO ()
main = runGUI

runGUI :: IO ()
runGUI = do
  (progName, _) <- getArgsAndInitialize
  createWindow progName
  displayCallback $= display
  reshapeCallback $= Just reshape
  keyboardMouseCallback $= Just keyboardMouse
  mainLoop

display :: IO ()
display = do
  clear [ ColorBuffer ]
  flush

reshape :: Size -> IO ()
reshape size = do
  viewport $= (Position 0 0, size)
  postRedisplay Nothing

keyboardMouse :: Key -> KeyState -> Modifiers -> Position -> IO () 
keyboardMouse key keyState modifiers position = do
  return ()
