module UnitTests where

import Test.HUnit
import Edge


networkHasLengthOfAtLeastMinNodes :: Test
networkHasLengthOfAtLeastMinNodes = 
  let min = 5
  in TestCase (assertBool "Network length must be at least MinNodes" ( buildRandomNetwork (mkStdGen 10) min 20 10))

 

directlyConnectedNodes =
  let n0 = Node "zero" es0
      n1 = Node "one" []
      es0 = [(Edge n0 n1 10)]
  in (n0, n1)

directlyConnectedNodesAreConnected :: Test
directlyConnectedNodesAreConnected = 
  let (n0, n1) = directlyConnectedNodes
  in TestCase (assertBool "DirectConnectedAreConnected" ( nodesConnected n0 n1 ) )

notConnectedNodesAreNotConnected :: Test
notConnectedNodesAreNotConnected =
  let (n1, n0) = directlyConnectedNodes
  in TestCase (assertBool "notConnected" (not (nodesConnected n1 n0)))


indirectlyConnectedNodes =
  let n0 = Node "zero" es0
      n1 = Node "one" es1
      n2 = Node "two" []
      es0 = [(Edge n0 n1 10)]
      es1 = [(Edge n1 n2 10)]
  in (n0, n2)

indirectlyConnectedNodesAreConnected :: Test
indirectlyConnectedNodesAreConnected = 
  let (n0, n2) = indirectlyConnectedNodes
  in TestCase (assertBool "indirectConnectedAreConnected" ( nodesConnected n0 n2 ) )


secondDegreeIndirectlyConnectedNodes =
  let n0 = Node "zero" es0
      n1 = Node "one" es1
      n2 = Node "two" es2
      n3 = Node "three" []
      es0 = [(Edge n0 n1 10)]
      es1 = [(Edge n1 n2 10)]
      es2 = [(Edge n2 n3 10)]
  in (n0, n3)

secondDegreeNodesAreConnected :: Test
secondDegreeNodesAreConnected = 
  let (n0, n3) = secondDegreeIndirectlyConnectedNodes
  in TestCase (assertBool "secondDegreeConnectedAreConnected" ( nodesConnected n0 n3 ) )







tests :: Test
tests = TestList [directlyConnectedNodesAreConnected, indirectlyConnectedNodesAreConnected, secondDegreeNodesAreConnected,  notConnectedNodesAreNotConnected]

main = runTestTT tests
