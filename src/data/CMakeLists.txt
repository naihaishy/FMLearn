
# Build data static lib
add_library(data STATIC data.cpp)

# Build unit tests
if (BUILD_UNIT_TEST)
    add_executable(data_test data_test.cpp)
    target_link_libraries(data_test gtest_main gtest data)
endif ()

set_target_properties(data PROPERTIES CLEAN_DIRECT_OUTPUT 1)