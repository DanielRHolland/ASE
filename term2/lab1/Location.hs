{-# LANGUAGE OverloadedStrings #-}

module Location where

import Data.Text.Lazy
import Data.Text.Lazy.Encoding
import Data.Aeson
import Control.Applicative

data Coord = Coord Double Double
  deriving (Show)

instance FromJSON Coord where
  parseJSON (Object v) = Coord <$>
                        v .: "x" <*>
                        v .: "y"

instance ToJSON Coord where
  toJSON (Coord x y) =
      object ["x" .= x,
              "y" .= y]


data Location = Location Integer Text Coord -- id name coord
  deriving (Show)

instance FromJSON Location where
  parseJSON (Object v) = Location <$>
                        v .: "id" <*>
                        v .:? "name" .!= "" <*>
                        v .: "coord"

instance ToJSON Location where
  toJSON (Location id name coord) = 
      object ["id" .= id,
              "name" .= name,
              "coord" .= coord]

data Route = Route Integer Text [Location]
  deriving (Show)

instance FromJSON Route where
  parseJSON (Object v) = Route <$>
                        v .: "id" <*>
                        v .:? "name" .!= "" <*>
                        v .: "locations"

instance ToJSON Route where
  toJSON (Route id name locations) =
      object ["id" .= id,
              "name" .= name,
              "locations" .= locations]
