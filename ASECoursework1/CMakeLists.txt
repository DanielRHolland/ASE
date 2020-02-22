cmake_minimum_required(VERSION 3.15)
project(ASECoursework)

set(CMAKE_CXX_STANDARD 14)

add_executable(ASECoursework main.cpp SerialBasketSolver.cpp UnorderedMapListBasketSolver.cpp)

add_executable(Test TestDictionary.cpp)