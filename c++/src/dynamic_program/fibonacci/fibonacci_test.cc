// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#include "dynamic_program/fibonacci/fibonacci.h"

#include <cstdio>

// ====================测试代码====================
void Test(uint32_t n, uint64_t expected) {
  if (FibonacciRecursive(n) == expected)
    printf("Test for %d in solution1 passed.\n", n);
  else
    printf("Test for %d in solution1 failed.\n", n);

  if (FibonacciIterative(n) == expected)
    printf("Test for %d in solution2 passed.\n", n);
  else
    printf("Test for %d in solution2 failed.\n", n);
}

int main(int argc, char* argv[]) {
  Test(0, 0);
  Test(1, 1);
  Test(2, 1);
  Test(3, 2);
  Test(4, 3);
  Test(5, 5);
  Test(6, 8);
  Test(7, 13);
  Test(8, 21);
  Test(9, 34);
  Test(10, 55);

  Test(40, 102334155);

  return 0;
}
