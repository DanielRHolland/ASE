


QuickCheck

In order to test the function `removeHeavierDuplicates` with a wider range of test data, the QuickCheck testing library was used. 

As the function takes a list of Edges as a parameter, `Edge` needed an instance declaration of `Arbitrary`. This allows QuickCheck to generate arbitrary Edges.


