
# Build loss static lib
add_library(loss STATIC loss.cpp squared_loss.cpp cross_entropy_loss.cpp)
set_target_properties(loss PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS loss DESTINATION ${BUILD_RESULT_DIR}/libs)

# Build unit tests
add_executable(loss_test loss_test.cpp)
target_link_libraries(loss_test gtest_main gtest data common loss)
install(TARGETS loss_test DESTINATION ${BUILD_RESULT_DIR}/test)
