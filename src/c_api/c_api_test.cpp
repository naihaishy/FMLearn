//
// Created by naihai on 2020/1/16.
// Google unit test for c_api module

#include "gtest/gtest.h"
#include "c_api.h"

TEST(C_API_TEST, FMMatrixCreateFromMat) {
  const float data[] = {1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
  };
  const float label[] = {1.0, 2.0, 3.0};
  DMatrix* dMatrix = new DMatrix();
  DataHandle* out = reinterpret_cast<DataHandle*>(&dMatrix);
  FMMatrixCreateFromMat(data, 3, 5, label, out);
  DMatrix* outMatrix = reinterpret_cast<DMatrix*>(*out);

  std::cout << "dMatrix address" << &dMatrix << std::endl;
  std::cout << "outMatrix address" << &outMatrix << std::endl;
  LOG_INFO(dMatrix);
  LOG_INFO(outMatrix);
  EXPECT_EQ(dMatrix, outMatrix);
}

int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

