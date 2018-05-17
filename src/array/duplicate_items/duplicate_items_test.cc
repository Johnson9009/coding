// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#include "array/duplicate_items/duplicate_items.h"

// ====================测试代码====================
bool contains(int array[], int length, int number) {
  for (int i = 0; i < length; ++i) {
    if (array[i] == number) return true;
  }

  return false;
}

void test(char const* testName, int numbers[], int lengthNumbers, int expected[],
          int expectedExpected, bool validArgument) {
  printf("%s begins: ", testName);
  try {
    int duplication = duplicate(numbers, lengthNumbers);
    if (validArgument == true) {
      if (contains(expected, expectedExpected, duplication)) {
        printf("Passed.\n");
      } else {
        printf("FAILED.\n");
      }
    } else {
      printf("FAILED.\n");
    }
  } catch (std::exception const& ia) {
    if (validArgument == false) {
      printf("Passed.\n");
    } else {
      printf("FAILED.\n");
    }
  }
}

// 重复的数字是数组中最小的数字
void test1() {
  int numbers[] = {2, 1, 3, 1, 4};
  int duplications[] = {1};
  test("Test1", numbers, sizeof(numbers) / sizeof(int), duplications,
       sizeof(duplications) / sizeof(int), true);
}

// 重复的数字是数组中最大的数字
void test2() {
  int numbers[] = {2, 4, 3, 1, 4};
  int duplications[] = {4};
  test("Test2", numbers, sizeof(numbers) / sizeof(int), duplications,
       sizeof(duplications) / sizeof(int), true);
}

// 数组中存在多个重复的数字
void test3() {
  int numbers[] = {2, 4, 2, 1, 4};
  int duplications[] = {2, 4};
  test("Test3", numbers, sizeof(numbers) / sizeof(int), duplications,
       sizeof(duplications) / sizeof(int), true);
}

// 没有重复的数字
void test4() {
  int numbers[] = {2, 1, 3, 0, 4};
  int duplications[] = {-1};  // not in use in the test function
  test("Test4", numbers, sizeof(numbers) / sizeof(int), duplications,
       sizeof(duplications) / sizeof(int), false);
}

// 没有重复的数字
void test5() {
  int numbers[] = {2, 1, 3, 5, 4};
  int duplications[] = {-1};  // not in use in the test function
  test("Test5", numbers, sizeof(numbers) / sizeof(int), duplications,
       sizeof(duplications) / sizeof(int), false);
}

// 无效的输入
void test6() {
  int* numbers = nullptr;
  int duplications[] = {-1};  // not in use in the test function
  test("Test6", numbers, 0, duplications, sizeof(duplications) / sizeof(int), false);
}

int main() {
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  return 0;
}
