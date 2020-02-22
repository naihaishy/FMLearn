//
// Created by naihai on 2020/1/31.
//

#include "gtest/gtest.h"

#include "cli/cli_param.h"
#include "cli/validator.h"

TEST(CLI_TEST, CliTrainParam) {
  CliTrainParam* param = new CliTrainParam();
  EXPECT_EQ(param->task, 0);
  EXPECT_EQ(param->model, 1);

  EXPECT_TRUE(param->train_file.empty());
  EXPECT_TRUE(param->valid_file.empty());
  EXPECT_TRUE(param->model_file.empty());

  EXPECT_EQ(param->n_factors, 10);
  EXPECT_EQ(param->n_epoch, 100);
  EXPECT_FLOAT_EQ(param->learning_rate, 0.1);
  EXPECT_FLOAT_EQ(param->reg_w0, 0.1);
  EXPECT_FLOAT_EQ(param->reg_W, 0.1);
  EXPECT_FLOAT_EQ(param->reg_V, 0.1);
  EXPECT_FLOAT_EQ(param->init_mean, 0.0);
  EXPECT_FLOAT_EQ(param->init_stddev, 0.1);

  EXPECT_EQ(param->n_thread, 1);
  EXPECT_EQ(param->seed, 0l);
  EXPECT_TRUE(param->norm);
  EXPECT_FALSE(param->quiet);

}

TEST(CLI_TEST, CliPredictionParam) {
  CliPredictionParam* param = new CliPredictionParam();
  EXPECT_TRUE(param->test_file.empty());
  EXPECT_TRUE(param->model_file.empty());
  EXPECT_TRUE(param->output_file.empty());

  EXPECT_TRUE(param->norm);
  EXPECT_EQ(param->n_thread, 1);
}

TEST(CLI_TEST, FMLearnCliParam) {
  FMLearnCliParam* param = new FMLearnCliParam();

  EXPECT_FALSE(param->IsTrain());
  EXPECT_TRUE(param->GetPredictionParam() != nullptr);
  EXPECT_TRUE(param->GetTrainParam() == nullptr);

  param->SetTrain();
  EXPECT_TRUE(param->IsTrain());
  EXPECT_TRUE(param->GetPredictionParam() == nullptr);
  EXPECT_TRUE(param->GetTrainParam() != nullptr);
}

TEST(CLI_TEST, Validate){
  CliTrainParam *param1  =new CliTrainParam();
  EXPECT_FALSE(Validator::Validate(*param1));
  param1->train_file = "data/house_price_train.txt";
  EXPECT_TRUE(Validator::Validate(*param1));

  CliPredictionParam *param2 = new CliPredictionParam();
  EXPECT_FALSE(Validator::Validate(*param2));
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

