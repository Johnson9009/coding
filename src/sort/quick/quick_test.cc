// Copyright (c) 2016 Johnson9009. All rights reserved.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files(the "Software"), to deal in the Software without restriction,
// including without limitation the rights to use, copy, modify, merge, publish, distribute,
// sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "sort/quick/quick-inl.h"

#include "gtest/gtest.h"

#define EXPECT_THROW_STREQ(statement, expected_exception, expected_string) \
  do {                                                                  \
    try {                                                               \
      statement;                                                        \
      FAIL() << "Expected: " << #statement << " throws an exception of type " \
             << #expected_exception << "." << std::endl                 \
             << "  Actual: it throws nothing.";                         \
    } catch (expected_exception const &e) {                             \
      EXPECT_STREQ(expected_string, e.what());                          \
    } catch (...) {                                                     \
      FAIL() << "Expected: " << #statement << " throws an exception of type " \
             << #expected_exception << "." << std::endl                 \
             << "  Actual: it throws a different type.";                \
    }                                                                   \
  } while (false)

TEST(GeneralTest, InvalidData) {
  EXPECT_THROW_STREQ(quick_sort(nullptr, 0, 0), std::invalid_argument, "data");
}

TEST(GeneralTest, NormalFunction) {
  int data[] = {9, 2, 8, 6, 7, 3, 2, 4, 1, 10};
  quick_sort(data, 0, 9);
  for (int i = 1; i < (sizeof(data) / sizeof(data[0])); ++i) {
    EXPECT_LE(data[i - 1], data[i]);
  }
}
