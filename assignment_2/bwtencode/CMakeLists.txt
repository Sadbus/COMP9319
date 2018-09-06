cmake_minimum_required(VERSION 3.12)
project(bwtencode)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -pedantic")

add_executable(bwtencode bwtencode.cpp)