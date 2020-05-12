module Plan where

import Data.IntMap.Lazy (IntMap)
import qualified Data.IntMap.Lazy as IntMap

type X = Double
type Y = Double
type Z = Double
data Dimensions = Dimensions X Y Z
data Orientation = Orientation X Y Z

type Name = String
data Product = Product Dimensions Name

data Element = Element Orientation Product

type Grid = IntMap Element
--data Grid = Grid []

data Plan = Plan Grid Name

instance Show Plan where
  show (Plan grid name) = 
    name ++ "\n" ++ (showGrid grid)

foldHelper::Element -> String -> String
foldHelper e s = " test " ++ s

--instance Show Grid where
--  show (Grid m) = IntMap.foldl (\a b -> " test " ++ b ) "" m
    --show g = IntMap.foldr (foldHelper) "" g
    --
showGrid g = IntMap.foldr (foldHelper) "" g


instance Show Element where
  show (Element orientation product) = show product

instance Show Product where
  show (Product dimensions name) =  name

type Position = Int
addElement::Grid -> Element -> Position -> Grid
addElement g element position = IntMap.insert position element g


