
# Build Shared Lib
add_library(FMLearn SHARED c_api.cpp c_api_error.cpp)
target_link_libraries(FMLearn data)
target_link_libraries(FMLearn model)

# Test for c_api
add_executable(c_api_test c_api_test.cpp)
target_link_libraries(c_api_test gtest_main gtest FMLearn)