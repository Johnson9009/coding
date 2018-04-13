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

#include <iostream>
#include <algorithm>

int partition(int *data, int first_idx, int last_idx) {
  int pivot_value = data[last_idx];

  int l = first_idx;
  int r = last_idx;

  while (l < r) {
    while ((l < r) && data[l] <= pivot_value) {
      ++l;
    }

    if (l < r) {
      data[r] = data[l];
      --r;
    }

    while ((r > l) && (data[r] >= pivot_value)) {
      --r;
    }

    if (r > l) {
      data[l] = data[r];
      ++l;
    }
  }

  data[l] = pivot_value;
  return l;
}

int partition2(int *data, int first_idx, int last_idx) {
  int small_idx = first_idx;
  for (int i = first_idx; i < last_idx; ++i) {
    if (data[i] < data[last_idx]) {
      if (i != small_idx) {
        std::swap(data[i], data[small_idx]);
      }
      ++small_idx;
    }
  }
  std::swap(data[small_idx], data[last_idx]);
  return small_idx;
}

void quick_sort(int *data, int first_idx, int last_idx) {
  // Must be >=, can not be ==.
  if ((data == nullptr) || (first_idx >= last_idx)) {
    return;
  }

  int pivot_idx = first_idx + ((last_idx - first_idx) >> 1);
  std::swap(data[pivot_idx], data[last_idx]);

  pivot_idx = partition2(data, first_idx, last_idx);
  quick_sort(data, first_idx, pivot_idx - 1);
  quick_sort(data, pivot_idx + 1, last_idx);
  return;
}

int main(int argc, char **argv) {
  int data[] = {9, 2, 8, 6, 7, 3, 2, 4, 1, 10};
  quick_sort(data, 0, 9);
  for (std::size_t i = 0; i < (sizeof(data) / sizeof(data[0])); ++i) {
    std::cout << data[i] << ", ";
  }
  std::cout << std::endl;
  return 0;
}
