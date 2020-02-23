//
// Created by naihai on 2020/1/16.
// Google unit test for c_api module

#include "gtest/gtest.h"

#include "c_api/c_api.h"
#include "c_api/c_api_error.h"
#include "data/data.h"
#include "model/hyper_param.h"

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



int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

