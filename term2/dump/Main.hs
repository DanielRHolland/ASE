module Main where
import SerialBofN
import System.Environment
import System.Exit

main :: IO ()
main = do
  [f] <- getArgs
  runSerialSolution f
