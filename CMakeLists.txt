cmake_minimum_required(VERSION 3.10)
project(FMLearn)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS -m64)
set(CMAKE_CXX_FLAGS -m64)

add_subdirectory(src/core)
add_subdirectory(src/c_api)
