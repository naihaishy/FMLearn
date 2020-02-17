
# Build score static lib
add_library(score STATIC score.cpp linear_score.cpp fm_score.cpp)
target_link_libraries(score common)
set_target_properties(score PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS score DESTINATION ${BUILD_RESULT_DIR}/libs)

# Build unit tests
add_executable(score_test score_test.cpp)
target_link_libraries(score_test gtest_main gtest data common score)
install(TARGETS score_test DESTINATION ${BUILD_RESULT_DIR}/test)