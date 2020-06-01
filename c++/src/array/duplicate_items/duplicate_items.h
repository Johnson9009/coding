// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

// 题3(一): 找出数组中重复的数字
// 题目: 在一个长度为n的数组里的所有数字都在0到n-1的范围内. 数组中某些数字是重复的, 但不知道有几个数
// 字重复了, 也不知道每个数字重复了几次. 请找出数组中任意一个重复的数字. 例如, 如果输入长度为7的数组
// {2, 3, 1, 0, 2, 5, 3}, 那么对应的输出是重复的数字2或者3.

#ifndef ARRAY_DUPLICATE_ITEMS_DUPLICATE_ITEMS_H_
#define ARRAY_DUPLICATE_ITEMS_DUPLICATE_ITEMS_H_

#include <stdexcept>
#include <utility>

int duplicate(int* data, int length) {
  if ((data == nullptr) || (length <= 1)) throw std::invalid_argument("");

  int pos = 0;
  while (pos < length) {
    int cur_value = data[pos];
    if (cur_value == pos) {
      ++pos;
    } else {
      if ((cur_value < 0) || (cur_value >= length)) throw std::invalid_argument("");

      if (cur_value == data[cur_value]) {
        return cur_value;
      } else {
        std::swap(data[pos], data[cur_value]);
      }
    }
  }
  throw std::invalid_argument("");
}

#endif  // ARRAY_DUPLICATE_ITEMS_DUPLICATE_ITEMS_H_
