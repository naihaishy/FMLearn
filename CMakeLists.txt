cmake_minimum_required(VERSION 3.5)
project(FMLearn)

set(CMAKE_CXX_STANDARD 11)
# set(CMAKE_C_FLAGS -m64)
# set(CMAKE_CXX_FLAGS -m64)
if (WIN32)
    #Windows
    if (MSVC)
        # 为VS2017设置参数
        if (NOT "${CMAKE_GENERATOR}" MATCHES "(Win64|IA64)")
        else ()
            set(CMAKE_GENERATOR_PLATFORM "Visual Studio 15 2017 Win64")
            set(CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE, "host=x64")
            add_definitions("/WX- /MD")
        endif ()
    endif ()
else ()
    #Linux
    add_definitions("-Wall -Wno-sign-compare -O3 -std=c++11
-march=native -Wno-strict-aliasing -Wno-comment")
endif ()


set(BUILD_UNIT_TEST true)


include_directories(
        "${PROJECT_SOURCE_DIR}"
        "${PROJECT_SOURCE_DIR}/src/common"
        "${PROJECT_SOURCE_DIR}/src/data"
        "${PROJECT_SOURCE_DIR}/src/core"
        "${PROJECT_SOURCE_DIR}/src/c_api"
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/gtest/include"
)


link_directories(
        "${PROJECT_BINARY_DIR}/src/common"
        "${PROJECT_BINARY_DIR}/src/data"
        "${PROJECT_BINARY_DIR}/src/core"
        "${PROJECT_BINARY_DIR}/src/c_api"
)


add_subdirectory(gtest)
add_subdirectory(src/common)
add_subdirectory(src/core)
add_subdirectory(src/data)
add_subdirectory(src/c_api)

add_library(fm_learn SHARED
        src/c_api/c_api.cpp
        src/c_api/c_api_error.cpp
        src/core/model.cpp
        src/core/fm_model.cpp
        src/data/data.cpp
        src/common/log.cpp src/loss/loss.cpp src/loss/loss.h src/loss/squared_loss.cpp src/loss/squared_loss.h src/loss/cross_entropy_loss.cpp src/loss/cross_entropy_loss.h)

# Set properties
set_target_properties(fm_learn PROPERTIES PREFIX "")
set_target_properties(fm_learn PROPERTIES OUTPUT_NAME "fm_learn")
set_target_properties(fm_learn PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# Scripts
if (WIN32)
    FILE(COPY "${PROJECT_SOURCE_DIR}/scripts/run_test.bat"
            DESTINATION ${CMAKE_BINARY_DIR})
else ()
    FILE(COPY "${PROJECT_SOURCE_DIR}/scripts/run_test.sh"
            DESTINATION ${CMAKE_BINARY_DIR})
endif ()

# 拷贝测试文件
FILE(COPY "${PROJECT_SOURCE_DIR}/python-package/fmlearn/house_price_train.txt"
        DESTINATION ${CMAKE_BINARY_DIR}/data)

install(TARGETS fm_learn DESTINATION ${CMAKE_BINARY_DIR})