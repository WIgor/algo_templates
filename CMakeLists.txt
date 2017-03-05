cmake_minimum_required(VERSION 3.6)
project(algo_templates)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp SegmentsTree.h FenwikTree.h PrefixFunction.h)
add_executable(algo_templates ${SOURCE_FILES})