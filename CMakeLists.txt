cmake_minimum_required(VERSION 3.5)
project(GraphAndScenery)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp CGraph.cpp CGraph.h ScenicSpot.h Path.h)
add_executable(GraphAndScenery ${SOURCE_FILES})