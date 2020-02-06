module Pythagoras where

sqr :: Double ->  Double
sqr x = x * x

pythagoras :: Double -> Double -> Double
pythagoras a b = sqrt(sqr a + sqr b)

promptForDouble :: String -> IO Double
promptForDouble message = do
    putStr message;
    readLn;
  

main :: IO ()
main = do 
    a <- promptForDouble "Enter the side:"
    b <- promptForDouble "Enter the base:"
    putStr "Hypotenuse: "
    print (pythagoras a b)
  
