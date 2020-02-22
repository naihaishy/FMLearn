//
// Created by naihai on 2020/1/28.
//

#include "gtest/gtest.h"

#include "score/score.h"
#include "score/fm_score.h"
#include "score/linear_score.h"
#include "core/hyper_param.h"

TEST(LOSS_TEST, Score) {
  Score* score1 = new FmScore();
  EXPECT_EQ(score1->GetType(), "FmScore");

  Score* score2 = new LinearScore();
  EXPECT_EQ(score2->GetType(), "LinearScore");
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}