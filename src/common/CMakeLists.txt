
# Build common static lib
add_library(common STATIC log.cpp utils.cpp)

# Test for common
if (BUILD_UNIT_TEST)
    if (WIN32)
        set(LIBS model data common gtest_main gtest)
    else ()
        set(LIBS model data common gtest_main gtest pthread)
    endif ()
    add_executable(common_test common_test.cpp)
    target_link_libraries(common_test ${LIBS})
endif ()

# Install library
install(TARGETS common DESTINATION ${CMAKE_BINARY_DIR}/lib/common)