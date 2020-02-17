
# Build model static lib
add_library(model STATIC model.cpp fm_model.cpp)
target_link_libraries(model common)
set_target_properties(model PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS model DESTINATION ${BUILD_RESULT_DIR}/libs)

if (WIN32)
    set(LIBS common loss score)
else ()
    set(LIBS common loss score pthread)
endif ()
target_link_libraries(model ${LIBS})

# Build unit tests
add_executable(model_test model_test.cpp)
target_link_libraries(model_test gtest_main gtest model data loss score)
install(TARGETS model_test DESTINATION ${BUILD_RESULT_DIR}/test)
