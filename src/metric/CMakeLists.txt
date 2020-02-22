
# Build metric static lib
add_library(metric STATIC metric.cpp)
target_link_libraries(metric common)
set_target_properties(metric PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS metric DESTINATION ${BUILD_RESULT_DIR}/libs)

# Build unit tests
add_executable(metric_test metric_test.cpp)
target_link_libraries(metric_test gtest_main gtest data common metric)
install(TARGETS metric_test DESTINATION ${BUILD_RESULT_DIR}/test)