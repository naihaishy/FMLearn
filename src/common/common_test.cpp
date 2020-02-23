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

TEST(COMMON_TEST, Check) {
  CHECK_LT(9, 12);
  CHECK_LT(12, 9);

  CHECK_GT(12, 9);
  CHECK_GT(9, 12);

  CHECK_LE(9, 9);
  CHECK_GE(12, 12);

  CHECK_EQ(12, 12);
  CHECK_EQ(true, true);
  CHECK_NE((12 == 12), false);
}

TEST(COMMON_TEST, Split_file) {
  std::vector<std::string> out_files;

  std::string base_file = "data/house_price_train.txt";

  int all_lines = get_file_lines(base_file); //1164
  int num_split = 3;
  LogInfo("all_lines " + std::to_string(all_lines) + " num_split "
               + std::to_string(num_split));

  split_file_in_lines(base_file, num_split, out_files);
  EXPECT_EQ(out_files.size(), num_split);

  std::vector<int> num_lines;
  for (const auto& file:out_files) {
    num_lines.push_back(get_file_lines(file));
    EXPECT_EQ(remove(file.c_str()), 0);
  }

  for (auto num_line:num_lines) {
    EXPECT_EQ(num_line, all_lines / num_split);
  }
}

void func(int id) {
  printf("Hello %i\n", id);
}

int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  LogInfo("\n");
  return RUN_ALL_TESTS();
}


