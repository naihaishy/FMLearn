

add_library(FMLearn_api SHARED c_api.cpp)

if(WIN32)
    target_link_libraries(FMLearn_api Ws2_32)
endif()