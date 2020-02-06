# Specify the minimum version for CMake

cmake_minimum_required(VERSION 2.8)

# Project's name
enable_testing()
project(BinarySearchTree)
# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
#include_directories("${PROJECT_SOURCE_DIR}")

set (SOURCES
  BinarySearchTree.cpp
)

add_executable(main main.cpp ${SOURCES})

add_executable(testbst TestBinarySearchTree.cpp)

add_test(
  NAME TestBinarySearchTree
  COMMAND testbst )
