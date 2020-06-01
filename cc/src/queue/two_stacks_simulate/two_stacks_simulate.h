// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

// 题9: 用两个栈实现队列
// 题目: 用两个栈实现一个队列. 队列的声明如下, 请实现它的两个函数Push和Pop, 分别完成在
// 队列尾部插入结点和在队列头部删除结点的功能.

#ifndef QUEUE_TWO_STACKS_SIMULATE_TWO_STACKS_SIMULATE_H_
#define QUEUE_TWO_STACKS_SIMULATE_TWO_STACKS_SIMULATE_H_

// #include <exception>
#include <stack>

template <typename T>
class Queue {
 public:
  void Push(T const& value);
  T Pop(void);

 private:
  std::stack<T> stack1_;
  std::stack<T> stack2_;
};

template <typename T>
void Queue<T>::Push(T const& value) {
  stack1_.push(value);
}

template <typename T>
T Queue<T>::Pop() {
  if (stack2_.empty() == true) {
    while (stack1_.empty() == false) {
      T data = stack1_.top();
      stack1_.pop();
      stack2_.push(data);
    }
  }

  if (stack2_.empty() == true) throw "queue is empty";

  T head = stack2_.top();
  stack2_.pop();

  return head;
}

#endif  // QUEUE_TWO_STACKS_SIMULATE_TWO_STACKS_SIMULATE_H_
