//
// Created by naihai on 2020/1/20.
//

#include "gtest/gtest.h"
#include "log.h"
#include <string>

TEST(COMMON_TEST, LOG_TEST){
  Logging::SetLevel(0);
  Logging::debug("debug");
  Logging::info("info");

  Logging::SetLevel(1);
  Logging::debug("debug");
  Logging::info("info");

  Logging::SetLevel("error");
  Logging::debug("debug");
  Logging::info("info");
  Logging::error("error");
}

int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


