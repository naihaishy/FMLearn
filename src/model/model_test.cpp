//
// Created by naihai on 2020/1/13.
// Google unit test for model module

#include "gtest/gtest.h"

#include "model/fm_model.h"
#include "model/hyper_param.h"
#include "model/model.h"
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

TEST(MODEL_TEST, FactorizationMachine) {
  // Constructor
  FactorizationMachine* fm = new FactorizationMachine(0, 10, 10,
                                                      0.1, 0.1, 0.1, 0.1,
                                                      0.0, 0.1, true, true);

  EXPECT_TRUE(fm != nullptr);

  // FMModel
  EXPECT_TRUE(fm->GetModel() != nullptr);

  // FMHyperParam
  EXPECT_TRUE(fm->GetHyperParam() != nullptr);
}

TEST(MODEL_TEST, FactorizationMachineFit) {

  // fm
  FactorizationMachine* fm = new FactorizationMachine(0, 10, 10,
                                                      0.1, 0.1, 0.1, 0.1,
                                                      0.0, 0.1,
                                                      true, true);

  // build data
  const float data[] = {1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
  };
  const float label[] = {1.0, 2.0, 3.0};

  int n_rows = 3;
  DMatrix* matrix = new DMatrix(data, label, n_rows, 5);

  // fit
  fm->Initialize();
  fm->Fit(matrix, 100);
}

TEST(MODEL_TEST, FactorizationMachinePredict){
  // fm
  FactorizationMachine* fm = new FactorizationMachine(0, 10, 10,
                                                      0.1, 0.1, 0.1, 0.1,
                                                      0.0, 0.1,
                                                      true, true);

  // build data
  const float train_data[] = {1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
  };
  const float train_label[] = {1.0, 2.0, 3.0};

  int n_rows = 3;
  DMatrix* train_matrix = new DMatrix(train_data, train_label, n_rows, 5);

  // fit
  fm->Initialize();
  fm->Fit(train_matrix, 100);

  // build test data
  const float test_data[] = {1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
  };
  DMatrix* test_matrix = new DMatrix(test_data, nullptr, 3, 5);

  const float* out = new float[3];

  std::vector<float > results = fm->Predict(test_matrix);
  out = &results[0];
  // fm->Predict(test_matrix, &out);
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

TEST(MODEL_TEST, Validate){
  TrainParam *param1  =new TrainParam();
  EXPECT_FALSE(Validator::Validate(*param1));
  param1->train_file = "data/house_price_train.txt";
  EXPECT_TRUE(Validator::Validate(*param1));

  PredictionParam *param2 = new PredictionParam();
  EXPECT_FALSE(Validator::Validate(*param2));
}

int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


