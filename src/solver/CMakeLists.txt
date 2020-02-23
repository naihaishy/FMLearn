
# Build solver static lib
add_library(solver STATIC solver.cpp trainer.cpp predictor.cpp)
target_link_libraries(solver data common model)
set_target_properties(solver PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS solver DESTINATION ${BUILD_RESULT_DIR}/libs)

# Build unit tests
add_executable(solver_test solver_test.cpp)
target_link_libraries(solver_test gtest_main gtest model data loss score solver)
install(TARGETS solver_test DESTINATION ${BUILD_RESULT_DIR}/test)
