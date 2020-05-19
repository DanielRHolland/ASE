{-# LANGUAGE TemplateHaskell #-}
module NetworkTests where

import Test.QuickCheck
import Test.HUnit
import Network
import System.Random

--instance Arbitrary Edge where
--    arbitrary = Edge <$> str <*> pos <*> pos <*> pos
--      where pos = getPositive <$> arbitrary
--            str = getString <$> arbitrary


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


prop_removeHeavierDuplicatesDoesNotReturnLongerList :: [Edge] -> Bool
prop_removeHeavierDuplicatesDoesNotReturnLongerList edges = length (removeHeavierDuplicates edges) <= length edges


prop_removeHeavierDuplicatesReturnsNoDuplicates :: [Edge] -> Bool
prop_removeHeavierDuplicatesReturnsNoDuplicates edges = noDuplicates ( removeHeavierDuplicates edges)


noDuplicates :: [Edge] -> Bool
noDuplicates [] = True
noDuplicates (e:edges) = length notDs == length edges && noDuplicates notDs 
    where notDs = filter (\x -> not (sameEnds e x)) edges


prop_chooseRandomPathResultNotLonger :: StdGen -> [Edge] -> Bool
prop_chooseRandomPathResultNotLonger g edges = length ( chooseRandomPath g edges ) <= length edges


prop_chooseRandomPathReturnsDifferentPathsForDifferentSeeds :: Int -> [Edge] -> Bool
prop_chooseRandomPathReturnsDifferentPathsForDifferentSeeds seed edges = (chooseRandomPath g0 edges /= chooseRandomPath g1 edges) || (length edges)<3
  where g0 = mkStdGen seed
        g1 = mkStdGen (seed+1)


differentStdGenGenerator :: Gen (StdGen, StdGen)
differentStdGenGenerator = suchThat (arbitrary :: Gen (StdGen,StdGen)) (
  \(g0,g1) -> 
    let (v0,_) = random g0 :: (Bool, StdGen)
        (v1,_) = random g1 :: (Bool, StdGen)
    in v0 /= v1)

notEmptyListGenerator :: Gen [Edge]
notEmptyListGenerator = suchThat (arbitrary :: Gen [Edge]) ((/=) [])


--prop_RevRev xs = reverse (reverse xs) == xs
--  where types = xs::[Int]


--prop_getAllEdgesLengthSame :: Network -> Bool
--prop_getAllEdgesLengthSame network = getAllEdges network



--secondDegreeNodesAreConnected :: Test
--secondDegreeNodesAreConnected = 
--  let (n0, n3) = secondDegreeIndirectlyConnectedNodes
--  in TestCase (assertBool "secondDegreeConnectedAreConnected" ( nodesConnected n0 n3 ) )


--1
getAllEdgesReturnsEmptyListFromEmptyArray :: Test
getAllEdgesReturnsEmptyListFromEmptyArray = TestCase (assertEqual "getAllEdges [] should return []" [] (getAllEdges []) )


getAllEdgesReturnsListOfEdges :: Test
getAllEdgesReturnsListOfEdges = TestCase (assertEqual "getAllEdges should return all edges of network" all_edges (getAllEdges network) )
  where 
      e0 = Edge "zero" 0 1 10
      e0a = Edge "zero_a" 0 2 15
      e1 = Edge "one" 1 2 10
      network = [Node "n_zero" [e0, e0a], Node "n_one" [e1], Node "n_two" []] :: Network
      all_edges = [e0, e0a, e1]

--2
removeHeavierDuplicatesRemovesNoneIfNoDuplicates :: Test
removeHeavierDuplicatesRemovesNoneIfNoDuplicates = TestCase (assertEqual "removeHeavierDuplicates removes nothing if no duplicates exist" allEdges (removeHeavierDuplicates allEdges))
  where
      allEdges = [Edge "zero" 0 1 10, Edge "zero_a" 0 2 15, Edge "one" 1 2 10]     

removeHeavierDuplicatesRemoves :: Test
removeHeavierDuplicatesRemoves = TestCase (assertEqual "removeHeavierDuplicates removes heaviest if duplicates exist" [allEdges!!0,allEdges!!2] (removeHeavierDuplicates allEdges))
  where
      allEdges = [Edge "zero" 0 1 10, Edge "zero_a" 0 1 15, Edge "one" 1 2 10]     

sameEndsFalseOnDiffEnds :: Test
sameEndsFalseOnDiffEnds = TestCase (assertBool "edges with different ends -> sameEnds = False" (not (sameEnds e0 e1)))
  where
      e0 = Edge "zero" 0 1 10
      e1 = Edge "one" 0 2 15     

sameEndsTrueOnSameEnds :: Test
sameEndsTrueOnSameEnds = TestCase (assertBool "edges with same ends -> sameEnds = True" (sameEnds e0 e1))
  where
      e0 = Edge "zero" 0 1 10
      e1 = Edge "one" 0 1 15     


tests :: Test
tests = TestList [getAllEdgesReturnsListOfEdges, getAllEdgesReturnsListOfEdges, removeHeavierDuplicatesRemovesNoneIfNoDuplicates, sameEndsFalseOnDiffEnds, sameEndsTrueOnSameEnds]

runUnitTests = runTestTT tests


-- weird for reasons here: http://hackage.haskell.org/package/QuickCheck-2.14/docs/Test-QuickCheck-All.html#v:quickCheckAll
return [] 
runPropTests = $quickCheckAll


runAllTests = do
                  runUnitTests
                  runPropTests
