
add_library(data SHARED data.cpp)

# Build unit tests
add_executable(data_test data_test.cpp)
target_link_libraries(data_test gtest_main gtest)
target_link_libraries(data_test FMLearn)

