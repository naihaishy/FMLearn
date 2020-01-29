
# Build common static lib
add_library(common STATIC log.cpp utils.cpp)

# Test for common
if (BUILD_UNIT_TEST)
    add_executable(common_test common_test.cpp)
    target_link_libraries(common_test gtest_main gtest model data common)
endif ()

# Install library
install(TARGETS common DESTINATION ${CMAKE_BINARY_DIR}/lib/common)