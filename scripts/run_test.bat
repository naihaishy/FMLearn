@echo off
REM # Test for running unit test
.\src\c_api\c_api_test.exe
.\src\common\common_test.exe
.\src\data\data_test.exe
.\src\core\model_test.exe
@pause