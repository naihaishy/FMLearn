
# Build loss static lib
add_library(loss STATIC loss.cpp squared_loss.cpp cross_entropy_loss.cpp)

# Build unit tests
if (BUILD_UNIT_TEST)
    add_executable(loss_test loss_test.cpp)
    target_link_libraries(loss_test gtest_main gtest data common loss)
endif ()

set_target_properties(loss PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# Install library
install(TARGETS loss DESTINATION ${CMAKE_BINARY_DIR}/lib/loss)