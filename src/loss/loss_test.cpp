//
// Created by naihai on 2020/1/28.
//

#include "gtest/gtest.h"

#include "loss/loss.h"
#include "loss/squared_loss.h"
#include "loss/cross_entropy_loss.h"

TEST(LOSS_TEST, Calculate) {
  Loss* loss1 = new SquaredLoss();
  EXPECT_EQ(loss1->GetType(), "SquaredLoss");

  Loss* loss2 = new CrossEntropyLoss();
  EXPECT_EQ(loss2->GetType(), "CrossEntropyLoss");

}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
