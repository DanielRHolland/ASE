{-# LANGUAGE TemplateHaskell #-}
module ShortestRouteTests where

import Test.QuickCheck
import Test.HUnit
import ShortestRoute
import System.Random
import TestDataGenerators


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


prop_chooseRandomPathReturnsDifferentPathsForDifferentRngs :: StdGenDiffPair -> EdgeListNonEmpty -> Bool
prop_chooseRandomPathReturnsDifferentPathsForDifferentRngs (StdGenDiffPair (g0, g1)) (EdgeListNonEmpty edges) = (chooseRandomPath g0 edges /= chooseRandomPath g1 edges)

prop_chooseRandomPathsHasSameLengthAsNumToGenerate :: StdGen -> [Edge] -> IntAtLeastOne -> Bool
prop_chooseRandomPathsHasSameLengthAsNumToGenerate g allEdges (IntAtLeastOne num) = num == length (chooseRandomPaths g allEdges num)


prop_chooseRandomPathsDiffersWithG :: StdGenDiffPair -> EdgeListNonEmpty -> IntAtLeastOne -> Bool
prop_chooseRandomPathsDiffersWithG (StdGenDiffPair (g0,g1)) (EdgeListNonEmpty allEdges) (IntAtLeastOne num) = (chooseRandomPaths g0 allEdges num /= chooseRandomPaths g1 allEdges num)


prop_chooseRandomPathsHasVariation :: StdGenFirstTwoDiffer -> EdgeListNonEmpty -> IntAtLeastOne -> Bool
prop_chooseRandomPathsHasVariation (StdGenFirstTwoDiffer g) (EdgeListNonEmpty allEdges) (IntAtLeastOne num) = any ((/=) p) ps
  where (p:ps) = chooseRandomPaths g allEdges (num+1)


prop_bestPathsReturnsCorrectNumber :: StdGen -> [ShortestRoute.Path] -> IntAtLeastOne -> Bool
prop_bestPathsReturnsCorrectNumber g paths (IntAtLeastOne num)  = x == length (bestPaths g paths num)
  where l = length paths
        x = if num > l then l else num




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
