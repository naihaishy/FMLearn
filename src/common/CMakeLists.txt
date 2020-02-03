
# Build common static lib
add_library(common STATIC log.cpp utils.cpp)
set_target_properties(common PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS common DESTINATION ${BUILD_RESULT_DIR}/libs)

# Build unit tests
if (WIN32)
    set(LIBS model data common gtest_main gtest)
else ()
    set(LIBS model data common gtest_main gtest pthread)
endif ()
add_executable(common_test common_test.cpp)
target_link_libraries(common_test ${LIBS})
install(TARGETS common_test DESTINATION ${BUILD_RESULT_DIR}/test)
