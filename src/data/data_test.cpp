//
// Created by naihai on 2020/1/13.
// Google unit test for data module

#include <src/c_api/c_api.h>
#include "gtest/gtest.h"

/**
 * 测试DMatrix默认构造函数
 */
TEST(DMATRIX_TEST, Construct_Default) {
  DMatrix matrix;
  EXPECT_EQ(matrix.has_label, true);
  EXPECT_EQ(matrix.row_length, 0);
  EXPECT_EQ(matrix.rows.empty(), true);
  EXPECT_EQ(matrix.labels.empty(), true);
  EXPECT_EQ(matrix.norms.empty(), true);
  EXPECT_FLOAT_EQ(matrix.max_label, std::numeric_limits<float>::min());
  EXPECT_FLOAT_EQ(matrix.min_label, std::numeric_limits<float>::max());
}

/**
 * 测试DMatrix显示构造函数 使用C数组指针
 */
TEST(DMATRIX_TEST, Construct_Explicit_Array) {
  const float data[] = {1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
                        1.0, 2.0, 3.0, 4.0, 5.0,
  };
  const float label[] = {1.0, 2.0, 3.0};

  int n_rows = 3;
  DMatrix* matrix = new DMatrix(data, label, n_rows, 5);
  EXPECT_TRUE(matrix->has_label);
  EXPECT_EQ(matrix->row_length, n_rows);
  EXPECT_EQ(matrix->rows.size(), n_rows);
  EXPECT_EQ(matrix->labels.size(), n_rows);
  EXPECT_EQ(matrix->norms.size(), n_rows);
  EXPECT_FLOAT_EQ(matrix->max_label, 3.0);
  EXPECT_FLOAT_EQ(matrix->min_label, 1.0);
}

/**
 * 测试DMatrix显示构造函数 使用C++ Vector
 */
TEST(DMATRIX_TEST, Construct_Explicit_Vector) {
  std::vector<std::vector<float >> data;
  data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});
  data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});
  data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});

  int n_rows = 3;
  std::vector<float> label = {1.0, 2.0, 3.0};
  DMatrix* matrix = new DMatrix(&data, &label);
  EXPECT_TRUE(matrix->has_label);
  EXPECT_EQ(matrix->row_length, n_rows);
  EXPECT_EQ(matrix->rows.size(), n_rows);
  EXPECT_EQ(matrix->labels.size(), n_rows);
  EXPECT_EQ(matrix->norms.size(), n_rows);
  EXPECT_FLOAT_EQ(matrix->max_label, 3.0);
  EXPECT_FLOAT_EQ(matrix->min_label, 1.0);
}

TEST(DMATRIX_TEST, Construct_Explicit_File) {
  std::string file_name = "data/house_price_train.txt";;
  DMatrix* matrix = new DMatrix(file_name, "txt", '\t', true);
  std::cout << matrix->GetNumFeatures() << std::endl;
}

/**
 * 测试DMatrix Init方法
 */
TEST(DMATRIX_TEST, Init) {
  DMatrix matrix;
  int n_rows = 3;
  matrix.Init(n_rows);

  EXPECT_EQ(matrix.rows.capacity(), n_rows);
  EXPECT_EQ(matrix.labels.capacity(), n_rows);
  EXPECT_EQ(matrix.norms.capacity(), n_rows);
}

/**
 * 测试DMatrix添加数据
 */
TEST(DMATRIX_TEST, AddData) {
  DMatrix matrix;
  matrix.Free();

  for (int i = 0; i < 10; ++i) {
    matrix.AddRow();
    matrix.labels[i] = 1.0 + i;
    matrix.norms[i] = 2.0 + i;
    matrix.AddNode(i, i, 12.12);
  }

  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(matrix.row_length, 10);
    EXPECT_EQ(matrix.labels[i], 1.0 + i);
    EXPECT_EQ(matrix.norms[i], 2.0 + i);
    SparseRow* row = matrix.rows[i];
    for (auto it = row->begin(); it != row->end(); ++it) {
      EXPECT_EQ(it->feature_id, i);
      EXPECT_FLOAT_EQ(it->feature_val, 12.12);
    }
  }
}

/**
 * 测试 DMatrix Free 方法
 */
TEST(DMATRIX_TEST, Free) {
  DMatrix matrix;
  matrix.Free();
  EXPECT_TRUE(matrix.has_label);
  EXPECT_EQ(matrix.row_length, 0);
  EXPECT_TRUE(matrix.rows.empty());
  EXPECT_TRUE(matrix.labels.empty());
  EXPECT_TRUE(matrix.norms.empty());
}

/**
 * 测试DMatrix 相等运算符
 */
TEST(DMATRIX_TEST, EQ) {
  std::vector<std::vector<float >> data;
  data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});
  data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});
  data.push_back({1.0, 2.0, 3.0, 4.0, 5.0});

  std::vector<float> label = {1.0, 2.0, 3.0};
  DMatrix* matrix1 = new DMatrix(&data, &label);
  DMatrix* matrix2 = new DMatrix(&data, &label);

  EXPECT_TRUE(*matrix1 == *matrix2);
  EXPECT_FALSE(*matrix1 != *matrix2);

  // change data
  data[0][0] = 9.0;
  DMatrix* matrix3 = new DMatrix(&data, &label);
  EXPECT_FALSE(*matrix1 == *matrix3);
  EXPECT_TRUE(*matrix1 != *matrix3);

  // change label
  data[0][0] = 1.0;
  label[0] = 9.0;
  DMatrix* matrix4 = new DMatrix(&data, &label);
  EXPECT_FALSE(*matrix1 == *matrix4);
  EXPECT_TRUE(*matrix1 != *matrix4);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

