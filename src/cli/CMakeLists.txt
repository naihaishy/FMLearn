# Build loss static lib
add_library(cmdline STATIC cmdline.cpp
        validate.h
        fmlearn.cpp)


add_executable(fmlearn_train fmlearn_train.cpp)
target_link_libraries(fmlearn_train model cmdline common data)
install(TARGETS fmlearn_train DESTINATION ${CMAKE_BINARY_DIR})


add_executable(fmlearn_predict fmlearn_predict.cpp)
target_link_libraries(fmlearn_predict model cmdline common data)
install(TARGETS fmlearn_predict DESTINATION ${CMAKE_BINARY_DIR})
