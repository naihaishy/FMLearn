@echo off
REM # Test for running unit test
.\test\c_api_test.exe
.\test\common_test.exe
.\test\cmdline_test.exe
.\test\data_test.exe
.\test\model_test.exe
.\test\loss_test.exe
.\test\score_test.exe
fmlearn_train data\house_price_train.txt fm.model -lr 0.0001 -e 10
fmlearn_predict data\house_price_test.txt fm.model
@pause