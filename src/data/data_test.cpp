//
// Created by naihai on 2020/1/13.
//
#include <src/c_api/c_api.h>
#include "gtest/gtest.h"

TEST(DMATRIX_TEST, Construct) {
  DMatrix matrix;
  EXPECT_EQ(matrix.has_label, true);
  EXPECT_EQ(matrix.row_length, 0);
  EXPECT_EQ(matrix.rows.empty(), true);
  EXPECT_EQ(matrix.labels.empty(), true);
  EXPECT_EQ(matrix.norms.empty(), true);
}

TEST(DMATRIX_TEST, Free) {
  DMatrix matrix;
  matrix.Free();
  EXPECT_EQ(matrix.has_label, true);
  EXPECT_EQ(matrix.row_length, 0);
  EXPECT_EQ(matrix.rows.empty(), true);
  EXPECT_EQ(matrix.labels.empty(), true);
  EXPECT_EQ(matrix.norms.empty(), true);
}

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

int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

