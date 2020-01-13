
add_library(FMLearn SHARED c_api.cpp c_api_error.cpp)
target_link_libraries(FMLearn model)