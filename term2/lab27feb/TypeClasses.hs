module TypeClasses where

data Colour = Red | Green | Blue | Purple | Magenta
  --deriving Show

isPrimary :: Colour -> Bool
isPrimary Red = True
isPrimary Green = True
isPrimary Blue = True
isPrimary _ = False


showColour :: Colour -> String
showColour Red = "Red-ish"
showColour Green = "Greenish"
showColour Blue = "Bluish"
showColour Purple = "Purplish"

instance Show Colour where
  show = showColour
