cmake_minimum_required(VERSION 2.4)

project(BinarySearchTree)

add_executable(app main.cpp BinarySearchTree.cpp HashTable.cpp)
add_executable(bsttest TestBinarySearchTree.cpp BinarySearchTree.cpp)
 

install (TARGETS app DESTINATION bin)