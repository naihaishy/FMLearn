// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// copy from https://github.com/chromium/chromium/blob/master/base/strings/stringprintf.h

#ifndef FMLEARN_COMMON_STRINGPRINTF_H_
#define FMLEARN_COMMON_STRINGPRINTF_H_

#include <cstdarg>   // va_list
#include <string>

std::string StringPrintf(const char* format, ...);
void SStringPrintf(std::string* dst, const char* format, ...);
void StringAppendF(std::string* dst, const char* format, ...);

void StringAppendV(std::string* dst, const char* format, va_list ap);

#endif  // FMLEARN_COMMON_STRINGPRINTF_H_
