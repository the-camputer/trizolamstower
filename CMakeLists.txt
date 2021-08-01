cmake_minimum_required(VERSION 3.16)

project(TrizolamsTower  VERSION 1.0
                        DESCRIPTION "Trizolam's Tower"
                        LANGUAGES CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++20")
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_subdirectory(src)
add_subdirectory(test)