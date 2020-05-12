module Testing where

import Test.QuickCheck

prop_reverseLength :: [Int] -> Bool
prop_reverseLength xs = 
  length xs == length (reverse xs)

prop_reverseInverse :: [Int] -> Bool
prop_reverseInverse xs =
  xs == reverse (reverse xs)

--prop_reverseHeadLast :: [Int] -> Bool
--prop_reverseHeadLast xs =
--  xs == [] || head xs == last (reverse xs)

prop_reverseHeadLast :: Int a => [a] -> Bool
prop_reverseHeadLast xs =
  xs == [] || head xs == last (reverse xs)

qsort :: Ord a => [a] -> [a]
qsort [] = []
qsort (x:xs) =
  let smaller = filter (< x) xs
      bigger = filter (>= x) xs
  in  qsort smaller ++ [x] ++ qsort bigger

prop_qsortIdempotent :: [Int] -> Bool
prop_qsortIdempotent xs =
  qsort xs == qsort (qsort xs)
  


