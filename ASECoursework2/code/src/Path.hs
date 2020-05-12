module Path where
import System.Random
import Data.Sort

type NodeId = Int

data Edge = Edge {
  start :: Int,
  end :: Int,
  weight :: Int} 
  deriving (Show)

type Path = [Edge]

data Node = Node {
  name :: String,
  nodeId :: Int
  }
  deriving (Show)

data Network = Network [Edge] [Node]
  deriving (Show)

scorePath :: Path -> Int
scorePath path = foldl (\ x edge -> (weight edge) + x) 0 path

topPaths :: [Path] -> Int -> [Path]
topPaths paths num = take num (sortOn scorePath paths)

topWithConnectable :: [Path] -> NodeId -> NodeId -> Int -> [Path]
topWithConnectable paths start end num = topPaths (filter (areNodesConnectable start end) paths) num

randPaths :: Int -> Int -> Int -> [Path]
randPaths seed num size = if num>0 then (randomPath seed) : (randPaths (seed+1) (num-1) size) else []

randomList :: Int -> [Int]
randomList seed = randoms (mkStdGen seed) :: [Int]

randomPath :: Int -> Path
randomPath seed = foldl (\xs s -> (randomEdge s) : xs) [] (take 25 (randomList seed))

randomEdge :: Int -> Edge
randomEdge seed = let a:b:c:xs = randomRs (1, 10) (mkStdGen seed) :: [Int]
  in Edge a b (head (randomRs (1, 100) (mkStdGen (seed*2)) :: [Int]))


areNodesConnectable :: NodeId -> NodeId -> [Edge] -> Bool
areNodesConnectable a b edges = any (\edge -> start edge == a && end edge == b) edges
                                || any (\x -> areNodesConnectable x b (filter (\e -> start e /= a) edges)) (getConnected a edges)

getConnected nodeId edges = foldl (\ns e -> if (start e) == nodeId then (end e):ns else ns) [] edges

genNodes :: Int -> Int -> [Node]
genNodes seed number = if number > 0 then (Node "dummy" number) : (genNodes seed (number-1)) else []

randomNetwork :: Int -> Int -> Network
randomNetwork seed size = Network (randomPath seed) (genNodes seed size)


