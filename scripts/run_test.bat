@echo off
REM # Test for running unit test
..\c_api\c_api_test.exe
..\common\common_test.exe
..\data\data_test.exe
..\core\model_test.exe
@pause