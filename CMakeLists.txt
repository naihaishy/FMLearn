cmake_minimum_required(VERSION 3.10)
project(FMLearn)

set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_C_FLAGS -m64)
# set(CMAKE_CXX_FLAGS -m64)

include_directories(
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/gtest/include"
)


link_directories(
        "${PROJECT_BINARY_DIR}/src/data"
        "${PROJECT_BINARY_DIR}/src/core"
        "${PROJECT_BINARY_DIR}/src/c_api"
)


add_subdirectory(gtest)
add_subdirectory(src/core)
add_subdirectory(src/data)
add_subdirectory(src/c_api)
