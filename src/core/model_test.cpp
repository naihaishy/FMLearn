//
// Created by naihai on 2020/1/13.
// Google unit test for model module

#include "gtest/gtest.h"
#include "fm_model.h"
#include "fm_param.h"
#include "model.h"

TEST(MODEL_TEST, FMModel) {
  int task = 0;
  int n_features = 10;
  int n_factors = 10;
  float mean = 0.1;
  float stddev = 0.1;
  // Constructor
  FMModel* model = new FMModel(task, n_features, n_factors, mean, stddev);
  EXPECT_EQ(model->task_, task);
  EXPECT_EQ(model->n_features_, n_features);
  EXPECT_EQ(model->n_factors_, n_factors);

  // InitWeights
  EXPECT_TRUE(model->W_ != nullptr);
  EXPECT_TRUE(model->V_ != nullptr);
  EXPECT_FLOAT_EQ(model->w0_, 0.0);
}

TEST(MODEL_TEST, FMHyperParam) {
  auto param = new FMHyperParam(0.1,
      0.1, 0.1, 0.1,
      true, false);
  EXPECT_FALSE(param->is_train);
  EXPECT_FALSE(param->on_disk);
  EXPECT_FALSE(param->verbose);

  EXPECT_FLOAT_EQ(param->learning_rate, 0.1);
  EXPECT_FLOAT_EQ(param->reg_W, 0.1);
  EXPECT_FLOAT_EQ(param->reg_W, 0.1);
  EXPECT_FLOAT_EQ(param->reg_V, 0.1);
  EXPECT_TRUE(param->norm);
  // std::cout << param->to_string() << std::endl;
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

  fm->Predict(test_matrix, &out);
}

int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


