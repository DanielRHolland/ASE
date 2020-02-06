{-# LANGUAGE OverloadedStrings #-}

-- http://seanhess.github.io/2015/08/19/practical-haskell-json-api.html is useful
module Main where

import Web.Scotty
import Data.Monoid (mconcat)
import Location

routes :: ScottyM ()
routes = do
  get "/hello" hello
  get "/goodbye" goodbye
  get "/loc" location 
  get "/rt/1" routeList
 

hello :: ActionM ()
hello = do
  html $ mconcat ["<h3>Hello World!</h3>"]

goodbye :: ActionM ()
goodbye = do
  html $ mconcat ["<h3>Goodbye!</h3>"]

location :: ActionM ()
location = do
  json $ Location 45 "Place 45" (Coord 45.23 12412.32)

routeList :: ActionM ()
routeList = do
  name <- param "name" `rescue` (\_ -> return "haskell")
  let loc1 = Location 321 "Place 321" (Coord 453.342 13231.32)
  let loc2 = Location 453 "Place 453" (Coord 3243.342 131.32)
  let locs = [loc1, loc2]
  let r1 = Route 1 name locs
  json $ r1

 
main = scotty 3000 routes  
