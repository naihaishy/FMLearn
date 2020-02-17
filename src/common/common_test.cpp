//
// Created by naihai on 2020/1/20.
//

#include "gtest/gtest.h"

#include "common/log.h"

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


void func(int id) {
  printf("Hello %i\n", id);
}



int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


