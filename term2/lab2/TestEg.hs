module TestEg where

import Test.HUnit
import Subjects

sqr0 :: Test
sqr0 = TestCase (assertEqual "sqr 0" (sqr 0) 0)

sqr1 :: Test
sqr1 = TestCase (assertEqual "sqr 1" (sqr 1) 1)

sqr2 :: Test
sqr2 = TestCase (assertEqual "sqr 2" (sqr 2) 4)

sqrTests :: Test
sqrTests = TestList [sqr0, sqr1, sqr2]

main = runTestTT sqrTests
