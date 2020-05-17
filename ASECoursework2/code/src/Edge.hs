module Edge where
import System.Random

maxNetworkSize = 30
maxEdgeWeight = 100

data Edge = Edge {
  start :: Node,
  end :: Node,
  weight :: Int}

instance Show Edge where
  show (Edge start end weight) = show ( (name start) ++ " -> " ++ (name end) ++ ",  Weight:  " ++ (show weight) )

type NodeId = String

data Node = Node {
  name :: NodeId,
  edges :: [Edge]}
  deriving (Show)

instance Eq Node where
  (Node n0 _) == (Node n1 _) = n0 == n1

type Network = [Node]

-- RNG, Min Nodes, Max Nodes, Max Edges per Node
buildRandomNetwork :: StdGen -> Int -> Int -> Int -> Network
buildRandomNetwork g minNodes maxNodes maxNodeEdges = 
  let (numberOfNodes, g0) = randomR (minNodes, maxNodes) g
  in reverse (addRandomEdges maxNodeEdges (buildEmptyNodes g0 numberOfNodes))

buildEmptyNodes :: StdGen -> Int -> [( StdGen , [Edge] -> Node)]
buildEmptyNodes _ 0 = []
buildEmptyNodes g n =
  let (_, g0) = next g
  in ( g0 , Node (show (n-1))) : buildEmptyNodes g0 (n-1)

addRandomEdges :: Int -> [( StdGen, [Edge] -> Node)] -> Network
addRandomEdges maxNodeEdges emptyNodes = 
  let network = map (\(g, en) -> let node = en (makeEdges g network node maxNodeEdges) in node) emptyNodes
  in network 

--addEdges :: StdGen -> Int -> [Edge] -> Node
--addEdges g max = if max > 0 then (\es -> )

makeEdges :: StdGen -> Network -> Node -> Int -> [Edge]
makeEdges _ _ _ 0 = []
makeEdges g network node n =
  let (end, g1) = randomR (0, (length network)-1) g
      (edgeWeight, g2) = randomR (1, maxEdgeWeight) g1
  in 
    (Edge node (network!!end) edgeWeight) : makeEdges g2 network node (n-1)


--
--

type Path = [Edge]

--pickRandomPath :: StdGen -> Network -> Path
--pickRandomPath g network =
--  let ()

nodesConnected :: Node -> Node -> Bool
nodesConnected = nodesConnectedRec [] 

nodesConnectedRec :: [NodeId] -> Node -> Node -> Bool
nodesConnectedRec alreadyVisited a b =
  let unvisitedNodes = filter (\x -> not(elem (name x) alreadyVisited)) (map end (edges a))
  in elem b unvisitedNodes
    || any (\node -> nodesConnectedRec ((name a):alreadyVisited) node b) unvisitedNodes


pathConnectsNodes :: Path -> Node -> Node -> Bool
pathConnectsNodes path a b =  
  let edgesStartingAtA = filter (\e -> (start e) == a) path
  in
    if null (edgesStartingAtA)
    then False
    else (any (\e -> (end e) == b) edgesStartingAtA)
        || (any (\e -> pathConnectsNodes path (end e) b) edgesStartingAtA)
 

networkEdges :: Network -> [Edge]
networkEdges ((Node name edges):ns) = edges ++ (networkEdges ns)
networkEdges [] = []

randomPath :: StdGen -> [Edge] -> Path
randomPath _ [] = []
randomPath g (e:es) =
  let (include, g0) = random g :: (Bool, StdGen)
  in (if include then e:(randomPath g0 es) else randomPath g0 es)


randomPaths :: StdGen -> [Edge] -> Int -> [Path]
randomPaths g edges 0 = []
randomPaths g edges n =
  let (_, g0) = next g
  in (randomPath g edges) : (randomPaths g0 edges (n-1))

 

--helper (e:edges) b = if (end e == b) then 

-- Is there an edge in path with a at start
-- yes -> does it end at b?
--     yes -> return True
--     no -> end of node is new a, restart
-- no -> False


