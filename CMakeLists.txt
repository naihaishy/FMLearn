cmake_minimum_required(VERSION 3.10)
project(FMLearn)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS -m64)
set(CMAKE_CXX_FLAGS -m64)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++")

set(BUILD_UNIT_TEST true)


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

add_library(fm_learn SHARED
        src/c_api/c_api.cpp
        src/c_api/c_api_error.cpp
        src/core/model.cpp
        src/data/data.cpp)

# Set properties
set_target_properties(fm_learn PROPERTIES OUTPUT_NAME "fm_learn")
set_target_properties(fm_learn PROPERTIES CLEAN_DIRECT_OUTPUT 1)

install(TARGETS fm_learn DESTINATION ${PROJECT_SOURCE_DIR}/build)