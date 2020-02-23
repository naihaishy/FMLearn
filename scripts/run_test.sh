#!/bin/bash
# Script for running unit test
mkdir log
./test/c_api_test
./test/common_test
./test/cmdline_test
./test/data_test
./test/model_test
./test/loss_test
./test/score_test
# train without validation file
./fmlearn_train data/house_price_train.txt fm.model -lr 0.001 -e 10 -t 0
# train with validation file
./fmlearn_train data/house_price_train.txt fm.model -v data/house_price_valid.txt -lr 0.001 -e 10 -t 0
# train in cross validation
./fmlearn_train data/house_price_train.txt fm.model -n_fold 3 -lr 0.001 -e 10 -t 0
# predict without output file
./fmlearn_predict data/house_price_test.txt fm.model
# predict with output file
./fmlearn_predict data/house_price_test.txt fm.model -o a.txt