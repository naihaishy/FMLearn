
# Build score static lib
add_library(score STATIC score.cpp linear_score.cpp fm_score.cpp)

# Build unit tests
if (BUILD_UNIT_TEST)
    add_executable(score_test score_test.cpp)
    target_link_libraries(score_test gtest_main gtest data common)
endif ()

set_target_properties(score PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# Install library
install(TARGETS score DESTINATION ${CMAKE_BINARY_DIR}/lib/score)