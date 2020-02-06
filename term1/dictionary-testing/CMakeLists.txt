cmake_minimum_required(VERSION 3.15)
project(dictionary_testing)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(dictionary_testing
        keyitemgenerator.cpp
        keyitemgenerator.h
        main.cpp)
