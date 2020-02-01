//
// Created by naihai on 2020/1/16.
// Google unit test for c_api module

#include "gtest/gtest.h"

#include "c_api/c_api.h"
#include "c_api/c_api_error.h"
#include "core/fm_param.h"
#include "core/model.h"
#include "data/data.h"


TEST(C_API_TEST, FMMatrixCreateFromMat) {
  const float data[] = {1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
  };
  const float label[] = {1.0, 2.0, 3.0};
  DMatrix* dMatrix = new DMatrix();
  DataHandle* out = reinterpret_cast<DataHandle*>(&dMatrix);
  FMMatrixCreateFromMat(data, 3, 5, label, out);
  DMatrix* matrix = reinterpret_cast<DMatrix*>(*out);

  std::cout << "dMatrix address" << &dMatrix << std::endl;
  std::cout << "outMatrix address" << &matrix << std::endl;
  EXPECT_EQ(dMatrix, matrix);
  EXPECT_EQ(matrix->row_length, 3);
  EXPECT_TRUE(matrix->has_label);
  EXPECT_EQ(matrix->labels.size(), 3);
  EXPECT_EQ(matrix->rows.size(), 3);
  EXPECT_EQ(matrix->norms.size(), 3);
}

TEST(C_API_TEST, FMMatrixCreateFromFile) {
  DMatrix* dMatrix = new DMatrix();
  DataHandle* out = reinterpret_cast<DataHandle*>(&dMatrix);
  std::string file_name = "data/house_price_train.txt";
  FMMatrixCreateFromFile(file_name, true, out);
  DMatrix* matrix = reinterpret_cast<DMatrix*>(*out);

  std::cout << "dMatrix address" << &dMatrix << std::endl;
  std::cout << "outMatrix address" << &matrix << std::endl;
  EXPECT_EQ(dMatrix, matrix);
  EXPECT_EQ(matrix->row_length, 1456);
  EXPECT_TRUE(matrix->has_label);
  EXPECT_EQ(matrix->labels.size(), 1456);
  EXPECT_EQ(matrix->rows.size(), 1456);
  EXPECT_EQ(matrix->norms.size(), 1456);
}

TEST(C_API_TEST, FMMatrixFree) {
  const float data[] = {1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
  };
  const float label[] = {1.0, 2.0, 3.0};
  DMatrix* dMatrix = nullptr;
  DataHandle* out = reinterpret_cast<DataHandle*>(&dMatrix);
  FMMatrixCreateFromMat(data, 3, 5, label, out);

  DMatrix* matrix = reinterpret_cast<DMatrix*>(*out);
  FMMatrixFree(out);

  EXPECT_TRUE(matrix->has_label);
  EXPECT_EQ(matrix->row_length, 0);
  EXPECT_TRUE(matrix->rows.empty());
  EXPECT_TRUE(matrix->labels.empty());
  EXPECT_TRUE(matrix->norms.empty());
}

TEST(C_API_TEST, FMCreate) {
  FactorizationMachine* dfm = nullptr;
  FM* out = reinterpret_cast<FM*>(&dfm);
  FMCreate(out, 0, 10, 20,
           0.1, 0.1, 0.1, 0.1,
           0.1, 0.1,
           true, true);

  FactorizationMachine* fm = reinterpret_cast<FactorizationMachine*>(*out);

  auto model = fm->GetModel();
  EXPECT_EQ(model->GetTask(), 0);
  EXPECT_EQ(model->GetNumFeatures(), 10);
  EXPECT_EQ(model->GetNumFactors(), 20);
  EXPECT_TRUE(model->GetW() != nullptr);
  EXPECT_TRUE(model->GetV() != nullptr);
  EXPECT_FLOAT_EQ(model->GetBias(), 0.0);

  auto param = new FMHyperParam(0.1,
                                0.1, 0.1, 0.1,
                                true, true);
  EXPECT_FALSE(param->is_train);
  EXPECT_FALSE(param->on_disk);

  EXPECT_FLOAT_EQ(param->learning_rate, 0.1);
  EXPECT_FLOAT_EQ(param->reg_W, 0.1);
  EXPECT_FLOAT_EQ(param->reg_W, 0.1);
  EXPECT_FLOAT_EQ(param->reg_V, 0.1);
  EXPECT_TRUE(param->norm);
  EXPECT_TRUE(param->verbose);
}

TEST(C_API_TEST, FMFit) {
  // build data
  std::vector<std::vector<float >> data;
  data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});
  data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});
  data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});

  int n_rows = 3;
  std::vector<float> label = {1.0, 2.0, 3.0};
  DMatrix* matrix = new DMatrix(&data, &label);
  DataHandle* data_out = reinterpret_cast<DataHandle*>(&matrix);

  // create fm
  FactorizationMachine* dfm = nullptr;
  FM* fm_out = reinterpret_cast<FM*>(&dfm);
  FMCreate(fm_out, 0, 10, 20,
           0.1, 0.1, 0.1, 0.1,
           0.1, 0.1, true, false);

  FactorizationMachine* fm = reinterpret_cast<FactorizationMachine*>(*fm_out);

  FMFit(fm_out, data_out, 100);
}

TEST(C_API_TEST, FMPredict) {
  // build data
  std::vector<std::vector<float >> data;
  data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});
  data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});
  data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});

  int n_rows = 3;
  DMatrix* matrix = new DMatrix(&data, nullptr);
  DataHandle* data_out = reinterpret_cast<DataHandle*>(&matrix);

  // create fm
  FactorizationMachine* dfm = nullptr;
  FM* fm_out = reinterpret_cast<FM*>(&dfm);
  FMCreate(fm_out, 0, 10, 20,
           0.1, 0.1, 0.1, 0.1,
           0.1, 0.1, true, false);

  FactorizationMachine* fm = reinterpret_cast<FactorizationMachine*>(*fm_out);

  float* dresult = new float[3];
  DataHandle* result_out = reinterpret_cast<DataHandle*>(&dresult);
  FMPredict(fm_out, data_out, result_out);
  const float** result = reinterpret_cast<const float**>(*result_out);
  for (int i = 0; i < 3; ++i) {
    std::cout << (*result)[i] << std::endl;
  }
}

TEST(C_API_TEST, FMGetLastError) {

}

int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

