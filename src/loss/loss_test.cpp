//
// Created by naihai on 2020/1/28.
//
#include "gtest/gtest.h"
#include "loss.h"
#include "squared_loss.h"
#include "cross_entropy_loss.h"

TEST(LOSS_TEST, Calculate) {
  Loss* loss = new SquaredLoss();
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
