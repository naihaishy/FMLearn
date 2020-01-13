
add_library(model SHARED model.cpp)
add_executable(main main.cpp)
target_link_libraries(main model)
