//
// Created by naihai on 2020/1/28.
//

#include "gtest/gtest.h"
#include "score.h"
#include "linear_score.h"
#include "fm_score.h"

TEST(LOSS_TEST, Calculate) {
  Score* score = new FmScore();
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}