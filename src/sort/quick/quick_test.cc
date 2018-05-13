// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

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
