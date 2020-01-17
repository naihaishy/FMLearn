//
// Created by naihai on 2020/1/13.
// Google unit test for model module

#include "model.h"
#include "gtest/gtest.h"

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
  auto param = new FMHyperParam();
  EXPECT_FALSE(param->is_train);
  EXPECT_FALSE(param->on_disk);
  EXPECT_FALSE(param->quiet);

  EXPECT_FLOAT_EQ(param->learning_rate, 0.1);
  EXPECT_FLOAT_EQ(param->reg_W, 0.1);
  EXPECT_FLOAT_EQ(param->reg_W, 0.1);
  EXPECT_FLOAT_EQ(param->reg_V, 0.1);
  EXPECT_TRUE(param->norm);
}

TEST(MODEL_TEST, FactorizationMachine) {
  // Constructor
  FactorizationMachine* fm = new FactorizationMachine(0, 10, 10,
                                                      0.1, 0.1, 0.1, 0.1,
                                                      0.0, 0.1);

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
                                                      0.0, 0.1);

  // build data
  const float data[] = {1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
  };
  const float label[] = {1.0, 2.0, 3.0};

  int n_rows = 3;
  DMatrix* matrix = new DMatrix(data, label, n_rows, 5);

  // fit
  fm->Fit(matrix, 100);
}

TEST(MODEL_TEST, FactorizationMachinePredict){
  // fm
  FactorizationMachine* fm = new FactorizationMachine(0, 10, 10,
                                                      0.1, 0.1, 0.1, 0.1,
                                                      0.0, 0.1);

  // build data
  const float data[] = {1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
  };
  const float label[] = {1.0, 2.0, 3.0};

  int n_rows = 3;
  DMatrix* train_matrix = new DMatrix(data, label, n_rows, 5);

  // fit
  fm->Fit(train_matrix, 100);

  // build test data
  std::vector<std::vector<float >> test_data;
  test_data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});
  test_data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});
  test_data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});
  DMatrix* test_matrix = new DMatrix(&test_data, nullptr);

  const float* out = new float[3];

  fm->Predict(test_matrix, &out);
}

int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


