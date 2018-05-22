// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#include "queue/two_stacks_simulate/two_stacks_simulate.h"

// ====================测试代码====================
void Test(char actual, char expected) {
  if (actual == expected)
    printf("Test passed.\n");
  else
    printf("Test failed.\n");
}

int main(int argc, char* argv[]) {
  Queue<char> queue;

  queue.Push('a');
  queue.Push('b');
  queue.Push('c');

  char head = queue.Pop();
  Test(head, 'a');

  head = queue.Pop();
  Test(head, 'b');

  queue.Push('d');
  head = queue.Pop();
  Test(head, 'c');

  queue.Push('e');
  head = queue.Pop();
  Test(head, 'd');

  head = queue.Pop();
  Test(head, 'e');

  return 0;
}
