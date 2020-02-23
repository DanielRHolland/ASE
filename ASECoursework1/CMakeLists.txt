cmake_minimum_required(VERSION 3.15)
project(ASECoursework)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")


set(CMAKE_CXX_STANDARD 14)

add_executable(ASECoursework main.cpp SerialBasketSolver.cpp UnorderedMapListBasketSolver.cpp MapListBasketSolver.cpp)

add_executable(Test TestDictionary.cpp)