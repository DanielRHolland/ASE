module SerialBofN where

{-# LANGUAGE ScopedTypeVariables #-}

import qualified Data.ByteString.Lazy as BL
import Data.Csv
import qualified Data.Vector as V
import Data.Sort

pr = putStrLn "Hello World"


--loadBasket filepath = do result <- parseFromFile csvFile filepath

--loadBasket :: string -> IO() -> Vector 
--loadBasket filepath = 



-- loadBasket :: FilePath -> IO () -- -> Maybe Vector (String, String)
--loadBasket filepath = do
   -- csvData <- ByteStringLazy.readFile filepath
   -- let list = []
  --  case decode NoHeader csvData of
  --    Left err -> putStrLn err
--      Right v -> Vector.forM_ v $ \i -> let list = i : list 
    
-- case decode NoHeader csvData of
       -- Left err -> putStrLn err
       -- Right v -> Vector.forM_ v $ \ (lName, rName) ->
       --     putStrLn $ lName ++ " : " ++ rName

type NamePair = (String, String)
type PosName = (Int, String)

loadBasket :: FilePath -> IO(Either String [NamePair])
loadBasket filePath = convertToList <$> BL.readFile filePath

convertToList :: BL.ByteString -> Either String [NamePair]
convertToList csvData = 
  case decode NoHeader csvData of
        Left err -> Left err 
        Right v -> Right( V.toList v )

serialAlgorithm basket =
  let
    x =  pt1 basket
  in
    pt2 x 2
  
pt1 :: [NamePair] -> ([NamePair], [PosName])
pt1 basket =   
  let 
    f = sortOn snd basket
    h = sortOn fst basket
  in
    pt1a f h (length f + 1)  

pt1a :: [NamePair] -> [NamePair] -> Int -> ([NamePair], [PosName])
pt1a [] _ n = ([],[])
pt1a _ [] n = ([],[])
pt1a (f:fs) (h:hs) n
  | snd f == fst h = 
    let
      next = pt1a fs hs n
    in
      ((fst f, snd h):(fst next), snd next)
  | snd (head fs) == fst h =
    let
      next = pt1a fs (h:hs) n
    in 
      (fst next, (n, snd f):(n-1, fst f):(snd next))
  | otherwise = pt1a (f:fs) hs n

pt2 :: ([NamePair], [PosName]) -> Int -> [PosName]
pt2 ([], posNames) _ = posNames
pt2 (namePairs, posNames) t =
  let
    f = sortOn snd namePairs
    g = sortOn snd posNames
    h = sortOn fst namePairs
  in
    pt2 (pt2a f g h t) (t*2)


pt2a :: [NamePair] -> [PosName] -> [NamePair] -> Int -> ([NamePair], [PosName])
pt2a [] _ _ _ = ([],[])
pt2a _ [] [] _ = ([],[])
--pt2a (f:fs) (g:gs) (h:hs) t
--  | (snd f) == (fst h) =
--    let 
--      next = pt2a fs (g:gs) hs t
--    in
--      ((fst f, snd h):(fst next), snd next) 
--  | (snd f) == (snd g) =
--    let
--      next = pt2a fs gs (h:hs) t
--    in
--      (fst next, ((fst g) - t, fst f):(snd next))
--  | (snd f) > (snd g) =   pt2a (f:fs) gs (h:hs) t
--  | (snd f) > (fst h) =   pt2a (f:fs) (g:gs) hs t
--pt2a (f:fs) [] (h:hs) t
--  | (snd f) == (fst h) =
--    let 
--      next = pt2a fs [] hs t
--    in
--      ((fst f, snd h):(fst next), snd next) 
--  | (snd f) > (fst h) =   pt2a (f:fs) [] hs t
--pt2a (f:fs) (g:gs) [] t
--  | (snd f) == (snd g) =
--    let
--      next = pt2a fs gs [] t
--    in
--      (fst next, ((fst g) - t, fst f):(snd next))
--  | (snd f) > (snd g) =   pt2a (f:fs) gs [] t
--pt2a _ g _ t = ([],[(-1, ("failure t:"++show t++" g:\n "++show g))])
pt2a fs [] hs t
  | x' == z =
    let 
      next = pt2a (tail fs) [] (tail hs) t
    in
      ((x, z'):(fst next), snd next) 
  | x' > z =   pt2a fs [] (tail hs) t 
  where
    (x, x') = head fs
    (z, z') = head hs
pt2a fs gs [] t  
  | x' == y' =
    let
      next = pt2a (tail fs) (tail gs) [] t
    in
      (fst next, (y - t, x):(snd next))
  | x' > y' =  pt2a fs (tail gs) [] t
  where
    (x, x') = head fs
    (y, y') = head gs
pt2a fs gs hs t
  | x' == z =
    let 
      next = pt2a (tail fs) gs (tail hs) t
    in
      ((x, z'):(fst next), snd next) 
  | x' == y' =
    let
      next = pt2a (tail fs) (tail gs) hs t
    in
      (fst next, (y - t, x):(snd next))
  | x' > y' =  pt2a fs (tail gs) hs t
  | x' > z =   pt2a fs gs (tail hs) t 
  where
    (x, x') = head fs
    (y, y') = head gs
    (z, z') = head hs
pt2a f g h t = ([],[(-1,show t ++ show f ++ show g ++ show h)])
    
runSerialSolution filePath = do
    output <- loadBasket filePath
    case output of
      Left err -> print err
      Right basket -> print (serialAlgorithm basket)
    

