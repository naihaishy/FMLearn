
#Build c_api static lib
add_library(c_api STATIC c_api.cpp c_api_error.cpp)


# Test for c_api
if (BUILD_UNIT_TEST)
    add_executable(c_api_test c_api_test.cpp)
    target_link_libraries(c_api_test gtest_main gtest c_api data model)
endif ()