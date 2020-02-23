//
// Created by naihai on 2020/1/13.
// Google unit test for model module

#include "gtest/gtest.h"

#include "model/fm_model.h"
#include "model/hyper_param.h"
#include "model/validator.h"

TEST(MODEL_TEST, FMModel) {
  int task = 0;
  int n_features = 10;
  int n_factors = 10;
  float mean = 0.1;
  float stddev = 0.1;
  // Constructor
  FMModel* model = new FMModel(task, n_features, n_factors, mean, stddev);
  EXPECT_EQ(model->GetTask(), task);
  EXPECT_EQ(model->GetNumFeatures(), n_features);
  EXPECT_EQ(model->GetNumFactors(), n_factors);

  // InitWeights
  EXPECT_TRUE(model->GetW() != nullptr);
  EXPECT_TRUE(model->GetV() != nullptr);
  EXPECT_FLOAT_EQ(model->GetBias(), 0.0);
}

TEST(MODEL_TEST, TrainParam) {
  TrainParam* param = new TrainParam();
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

TEST(MODEL_TEST, PredictionParam) {
  PredictionParam* param = new PredictionParam();
  EXPECT_TRUE(param->test_file.empty());
  EXPECT_TRUE(param->model_file.empty());
  EXPECT_TRUE(param->output_file.empty());

  EXPECT_TRUE(param->norm);
  EXPECT_EQ(param->n_thread, 1);
}

TEST(MODEL_TEST, HyperParam) {
  HyperParam* param = new HyperParam();

  EXPECT_TRUE(param->is_train);
  EXPECT_TRUE(param->GetPredictionParam() == nullptr);
  EXPECT_TRUE(param->GetTrainParam() != nullptr);

  param->is_train = false;
  EXPECT_FALSE(param->is_train);
  EXPECT_TRUE(param->GetPredictionParam() != nullptr);
  EXPECT_TRUE(param->GetTrainParam() == nullptr);
}

TEST(MODEL_TEST, Validate) {
  TrainParam* param1 = new TrainParam();
  EXPECT_FALSE(Validator::Validate(*param1));
  param1->train_file = "data/house_price_train.txt";
  EXPECT_TRUE(Validator::Validate(*param1));

  PredictionParam* param2 = new PredictionParam();
  EXPECT_FALSE(Validator::Validate(*param2));
}

int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


