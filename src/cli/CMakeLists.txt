
# Build loss static lib
add_library(cmdline STATIC cmdline.cpp)
target_link_libraries(cmdline common)
set_target_properties(cmdline PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS cmdline DESTINATION ${BUILD_RESULT_DIR}/libs)

add_executable(fmlearn_train fmlearn_train.cpp)
target_link_libraries(fmlearn_train model cmdline common data solver metric)
install(TARGETS fmlearn_train DESTINATION ${BUILD_RESULT_DIR})

add_executable(fmlearn_predict fmlearn_predict.cpp)
target_link_libraries(fmlearn_predict model cmdline common data solver metric)
install(TARGETS fmlearn_predict DESTINATION ${BUILD_RESULT_DIR})

# Build unit tests
add_executable(cmdline_test cli_test.cpp)
target_link_libraries(cmdline_test gtest_main gtest data common cmdline)
install(TARGETS cmdline_test DESTINATION ${BUILD_RESULT_DIR}/test)
