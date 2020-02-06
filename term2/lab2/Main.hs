{-# LANGUAGE OverloadedStrings #-}


module Main where

decomposeID :: String -> (Char, Int)
decomposeID str = (head str, read (tail str))

main = do 
    putStr "Hello World"
    let nNumber = "N0697611"
    let pair = decomposeID nNumber
    putChar (fst pair)
    let ls = [1,2,3,4,5]
    let rls = rev ls
    let rrls = rev rls 
    print ls
   
