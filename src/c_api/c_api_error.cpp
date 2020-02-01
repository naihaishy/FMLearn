//
// Created by naihai on 2020/1/12.
//

#include "c_api/c_api_error.h"

struct FMAPIErrorEntry {
  std::string last_error;
};

static FMAPIErrorEntry entry;

const char* FMGetLastError() {
  return entry.last_error.c_str();
}

void FMAPISetLastError(const char* msg) {
  entry.last_error = std::string(msg);
}