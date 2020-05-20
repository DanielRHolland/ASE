module TestDataGenerators where

import Test.QuickCheck
import System.Random
import Network


instance Arbitrary Edge where
    arbitrary = do
        n <- arbitrary
        Positive s <- arbitrary
        Positive e <- arbitrary
        Positive w <- arbitrary
        return (Edge n s e w)
       

instance Arbitrary StdGen where
    arbitrary = do
        x <- arbitrary
        return (mkStdGen x)

newtype StdGenDiffPair = StdGenDiffPair (StdGen, StdGen)
  deriving Show

instance Arbitrary StdGenDiffPair where
 arbitrary = do 
      gs <- suchThat (arbitrary :: Gen (StdGen, StdGen)) (
        \(g0,g1) -> 
          let (v0,_) = random g0 :: (Bool, StdGen)
              (v1,_) = random g1 :: (Bool, StdGen)
          in v0 /= v1)
      return (StdGenDiffPair gs)

newtype EdgeListNonEmpty = EdgeListNonEmpty [Edge]
  deriving Show

instance Arbitrary EdgeListNonEmpty where
  arbitrary = do
            xs <- suchThat (arbitrary :: Gen [Edge]) ((/=) [])
            return (EdgeListNonEmpty xs)
         

newtype IntAtLeastOne = IntAtLeastOne Int
    deriving Show

instance Arbitrary IntAtLeastOne where
  arbitrary = do
      x <- suchThat (arbitrary :: Gen Int) ((<=) 1)
      return (IntAtLeastOne x)


newtype StdGenFirstTwoDiffer = StdGenFirstTwoDiffer StdGen
  deriving Show

instance Arbitrary StdGenFirstTwoDiffer where
  arbitrary = do
      x <- suchThat (arbitrary :: Gen StdGen) (
          \g -> 
            let (v0,g0) = random g :: (Bool, StdGen)
                (v1,_) = random g0 :: (Bool, StdGen)
            in  v0 /= v1)
      return (StdGenFirstTwoDiffer x)
