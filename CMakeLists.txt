cmake_minimum_required(VERSION 3.15)
project(FMLearn)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D__FILENAME__='\"$(subst  ${CMAKE_SOURCE_DIR}/src/,,$(abspath $<))\"'")
#set(CMAKE_BUILD_TYPE RELEASE)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")

if (WIN32)
    #Windows
    if (MSVC)
        # 为VS2017设置参数
        if (NOT "${CMAKE_GENERATOR}" MATCHES "(Wino64|IA64)")
        else ()
            # set(CMAKE_GENERATOR_PLATFORM "Visual Studio 15 2017 Win64")
            set(CMAKE_VS_PLATFORM_TOOLSET_HOST_ARCHITECTURE, "host=x64")
            add_definitions("/WX- /MD")
        endif ()
    endif ()
else ()
    #Linux
    add_definitions("-Wall -Wno-sign-compare -march=native -Wno-strict-aliasing -Wno-comment")
endif ()

# 保存编译结果的目录
set(BUILD_RESULT_DIR ${PROJECT_BINARY_DIR}/results/)

include_directories(
        "${PROJECT_SOURCE_DIR}/src"
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/gtest/include"
)


link_directories(
        "${PROJECT_BINARY_DIR}/src/common"
        "${PROJECT_BINARY_DIR}/src/data"
        "${PROJECT_BINARY_DIR}/src/loss"
        "${PROJECT_BINARY_DIR}/src/score"
        "${PROJECT_BINARY_DIR}/src/core"
        "${PROJECT_BINARY_DIR}/src/metric"
        "${PROJECT_BINARY_DIR}/src/c_api"
        "${PROJECT_BINARY_DIR}/src/cli"
)


add_subdirectory(gtest)
add_subdirectory(src/common)
add_subdirectory(src/data)
add_subdirectory(src/loss)
add_subdirectory(src/score)
add_subdirectory(src/solver)
add_subdirectory(src/metric)
add_subdirectory(src/cli)
add_subdirectory(src/model)
add_subdirectory(src/c_api)

# 拷贝测试脚本与测试数据
if (WIN32)
    FILE(COPY "${PROJECT_SOURCE_DIR}/scripts/run_test.bat" DESTINATION ${BUILD_RESULT_DIR})
else ()
    FILE(COPY "${PROJECT_SOURCE_DIR}/scripts/run_test.sh" DESTINATION ${BUILD_RESULT_DIR})
endif ()

FILE(COPY "${PROJECT_SOURCE_DIR}/python-package/fmlearn/house_price_train.txt"
        DESTINATION ${BUILD_RESULT_DIR}/data)
FILE(COPY "${PROJECT_SOURCE_DIR}/python-package/fmlearn/house_price_test.txt"
        DESTINATION ${BUILD_RESULT_DIR}/data)

file(GLOB HEADER_FILES "${PROJECT_SOURCE_DIR}/src/*/*.h")
install(FILES ${HEADER_FILES} DESTINATION ${BUILD_RESULT_DIR}/include)