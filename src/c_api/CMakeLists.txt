
#Build c_api static lib
add_library(c_api STATIC c_api.cpp c_api_error.cpp)
target_link_libraries(c_api common)
set_target_properties(c_api PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS c_api DESTINATION ${BUILD_RESULT_DIR}/libs)

# Build unit tests
add_executable(c_api_test c_api_test.cpp)
target_link_libraries(c_api_test gtest_main gtest c_api data model)
install(TARGETS c_api_test DESTINATION ${BUILD_RESULT_DIR}/test)

# 构建核心dll
add_library(fm_learn SHARED
        c_api.cpp
        c_api_error.cpp
        ../core/model.cpp
        ../core/fm_model.cpp
        ../data/data.cpp
        ../data/reader.cpp
        ../common/log.cpp
        ../common/utils.cpp
        ../loss/loss.cpp
        ../loss/squared_loss.cpp
        ../loss/cross_entropy_loss.cpp
        ../score/score.cpp
        ../score/linear_score.cpp
        ../score/fm_score.cpp
        ../cli/cmdline.cpp
        ../cli/cli_param.cpp)

set_target_properties(fm_learn PROPERTIES PREFIX "")
set_target_properties(fm_learn PROPERTIES OUTPUT_NAME "fm_learn")
set_target_properties(fm_learn PROPERTIES CLEAN_DIRECT_OUTPUT 1)
install(TARGETS fm_learn DESTINATION ${BUILD_RESULT_DIR})
