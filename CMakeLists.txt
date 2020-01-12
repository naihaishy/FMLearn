cmake_minimum_required(VERSION 3.10)
project(FMLearn)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS -m64)
set(CMAKE_CXX_FLAGS -m64)

add_library(FMLearn SHARED src/c_api/c_api.cpp src/c_api/c_api.h src/c_api/c_api_error.h src/c_api/c_api_error.cpp)