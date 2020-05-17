module PathTests where

import Test.QuickCheck
import System.Random
import Edge

--buildRandomNetwork
--

-- :: Test
--networkHasFewerThanMaxNodes = TestCase (  )

--networkHasAtLeastTwoNodes

--networkNodes

--prop_rNetworkHasNoMoreThanMaxNodes :: Int -> Bool
--prop_rNetworkHasNoMoreThanMaxNodes seed =
--  let maxNodes = choose(0,200)
--  in length ( buildRandomNetwork (mkStdGen seed) choose(0,20) maxNodes choose(0, 20) ) <= maxNodes

prop_rNetworkHasAtLeastTwoNodes :: Int -> Int -> Int -> Int -> Bool
prop_rNetworkHasAtLeastTwoNodes seed minNodes maxNodes maxNodeEdges =  length ( buildRandomNetwork (mkStdGen seed)  maxNodes minNodes maxNodeEdges ) >= 2

prop_buildEmptyNodesHasLengthGiven :: Int -> Int -> Bool
prop_buildEmptyNodesHasLengthGiven seed n = n == length (buildEmptyNodes (mkStdGen seed) n)




--prop_randomPath
