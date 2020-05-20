module Network where
import Data.Sort
import System.Random

type Network = [Node]

type Path = [Edge]

data Node = Node {
  nodeName :: String,
  edges :: [Edge]}

data Edge = Edge {
  edgeName :: String,
  start :: Int,
  end :: Int,
  weight :: Int}
  deriving (Show, Eq)

getAllEdges :: Network -> [Edge]
getAllEdges [] = []
getAllEdges (n:ns) = (edges n) ++ (getAllEdges ns)


removeHeavierDuplicates :: [Edge] -> [Edge]
removeHeavierDuplicates [] = []
removeHeavierDuplicates l = 
    let ds = filter (sameEnds (head l)) l
        lightest = head (reverse (sortOn weight ds))
        es = filter (\x -> not (sameEnds x (head l))) l 
    in lightest : (removeHeavierDuplicates es) 

sameEnds :: Edge -> Edge -> Bool
sameEnds a b = (start a) == (start b) && (end a) == (end b)


chooseRandomPath :: StdGen -> [Edge] -> Path
chooseRandomPath _ [] = []
chooseRandomPath g (e:es) = if b0 then chooseRandomPath g0 es else e:(chooseRandomPath g0 es)
    where (b0, g0) = random g :: (Bool, StdGen)


chooseRandomPaths :: StdGen -> [Edge] -> Int -> [Path]
chooseRandomPaths g edges num 
                | num <= 0 = []
                | otherwise = (chooseRandomPath g edges) : (chooseRandomPaths g0 edges (num-1))
              where (_,g0) = next g


