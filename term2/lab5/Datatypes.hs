module Datatypes where

type Radius = Double
type Side = Double

data Shape = Circle Radius
            | Rectangle Side Side
            | Hexagon Side Side Side Side Side Side 


isRound :: Shape -> Bool
isRound (Circle r) = True
isRound (Rectangle x y) = False

--area :: Shape -> Double
--area (Circle r) = 


data EgList = EndOfList
            | Node Int EgList

egListLength :: EgList -> Int
egListLength EndOfList = 0
egListLength (Node _ l) = 1 + egListLength l

type Key = Int
type Item = String

data EgBST = Leaf
            | BstNode Key Item EgBST EgBST

data MaybeItem = EgNothing
                | EgJust Item

egLookup :: Key -> EgBST -> MaybeItem
egLookup soughtKey Leaf = EgNothing
egLookup soughtKey (BstNode k i leftC rightC) = 
  if soughtKey < k then
    egLookup soughtKey leftC
  else if soughtKey > k then
    egLookup soughtKey rightC
  else
    EgJust i
