#!/bin/bash
# Script for running unit test
./src/c_api/c_api_test
./src/common/common_test
./src/data/data_test
./src/core/model_test
./src/cli/cli_test
./src/loss/loss_test
./src/score/score_test
./fmlearn_train data/house_price_train.txt fm.model -lr 0.0001 -e 10
./fmlearn_predict data/house_price_test.txt fm.model