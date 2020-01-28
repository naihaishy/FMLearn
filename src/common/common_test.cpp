//
// Created by naihai on 2020/1/20.
//

#include "gtest/gtest.h"
#include "log.h"
#include "thread_pool.h"
#include <string>

TEST(COMMON_TEST, Logging) {
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


void func(int id) {
  printf("Hello %i\n", id);
}

TEST(COMMON_TEST, ThreadPool) {
  ThreadPool pool(4);
  for (int i = 0; i < 3; ++i) {
    pool.enqueue(std::bind(func, 1));
    pool.enqueue(std::bind(func, 2));
    pool.enqueue(std::bind(func, 3));
    pool.enqueue(std::bind(func, 4));
    pool.enqueue(std::bind(func, 5));
    pool.enqueue(std::bind(func, 6));
    printf("Hello master\n");
  }
  printf("final\n");
}

int main(int argc, char* argv[]) {

  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}


