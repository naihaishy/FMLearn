
# Build model static lib
add_library(model STATIC model.cpp fm_model.cpp)
target_link_libraries(model common)

# Test for model
if (BUILD_UNIT_TEST)
    add_executable(model_test model_test.cpp)
    target_link_libraries(model_test gtest_main gtest model data)
endif ()

set_target_properties(model PROPERTIES CLEAN_DIRECT_OUTPUT 1)