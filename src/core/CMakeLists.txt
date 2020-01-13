
add_library(model SHARED model.cpp)

# Test for model
add_executable(model_test model_test.cpp)
target_link_libraries(model_test model)
