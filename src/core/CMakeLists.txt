
# Build model static lib
add_library(model STATIC model.cpp fm_model.cpp)
if (WIN32)
    set(LIBS common loss score)
else ()
    set(LIBS common loss score pthread)
endif ()
target_link_libraries(model ${LIBS})

# Test for model
if (BUILD_UNIT_TEST)
    add_executable(model_test model_test.cpp)
    target_link_libraries(model_test gtest_main gtest model data loss score)
endif ()

set_target_properties(model PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# Install library
install(TARGETS model DESTINATION ${CMAKE_BINARY_DIR}/lib/model)