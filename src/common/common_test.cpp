//
// Created by naihai on 2020/1/20.
//

#include "gtest/gtest.h"

#include "common/log.h"
#include "common/check.h"
#include "common/utils.h"

TEST(COMMON_TEST, Logging) {
  Logging::SetLevel(0);
  SetLoggingDir("log");
  LogDebug("debug");
  LogInfo("info");

  Logging::SetLevel(1);
  LogDebug("debug");
  LogInfo("info");

  Logging::SetLevel("error");
  LogDebug("debug");
  LogInfo("info");
  LogError("error");
  LogInfo("Hello");

}

TEST(COMMON_TEST, Check){
  CHECK_LT(9, 12);
  CHECK_LT(12, 9);

  CHECK_GT(12, 9);
  CHECK_GT(9, 12);

  CHECK_LE(9, 9);
  CHECK_GE(12, 12);

  CHECK_EQ(12, 12);
  CHECK_EQ(true, true);
  CHECK_NE((12==12), false);
}

TEST(COMMON_TEST, Split_file){
  std::vector<std::string> out_files;
  split_file_in_lines("data/house_price_train.txt", 3, out_files);
  EXPECT_EQ(out_files.size(), 3);
  // remove
  EXPECT_TRUE(remove("data/house_price_train.txt_0"));
  EXPECT_TRUE(remove("data/house_price_train.txt_1"));
  EXPECT_TRUE(remove("data/house_price_train.txt_2"));
}


void func(int id) {
  printf("Hello %i\n", id);
}



int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  LogInfo("\n");
  return RUN_ALL_TESTS();
}


