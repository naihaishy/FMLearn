@echo off
REM # Test for running unit test
.\src\c_api\c_api_test.exe
.\src\common\common_test.exe
.\src\data\data_test.exe
.\src\core\model_test.exe
fmlearn_train data\house_price_train.txt fm.model -lr 0.0001 -e 10
fmlearn_predict data\house_price_test.txt fm.model
@pause