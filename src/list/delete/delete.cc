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

struct LinkNode {
  LinkNode(int var, LinkNode *next_node): value(var), next(next_node) {}
  int value;
  LinkNode * next;
};


void insert(LinkNode **head, int pos, int value) {
  if (head == nullptr) {
    std::cout << "error head!" << std::endl;
    return;
  }

  if (pos <= 0) {
    *head = new LinkNode(value, *head);
    return;
  }

  LinkNode *previous = *head;
  for (int i = 0; i < (pos - 1); ++i) {
    if ((previous == nullptr) || (previous->next == nullptr)) {
      std::cout << "error head or pos!" << std::endl;
      return;
    } else {
      previous = previous->next;
    }
  }

  previous->next = new LinkNode(value, previous->next);
  return;
}

void delete_node(LinkNode **head, int pos) {
  if (head == nullptr) {
    std::cout << "error head!" << std::endl;
    return;
  }

  if (pos <= 0) {
    if (*head == nullptr) {
      std::cout << "head is null!" << std::endl;
    } else {
      LinkNode *temp = *head;
      *head = (*head)->next;
      delete temp;
    }
    return;
  }

  LinkNode *previous = *head;
  for (int i = 0; i < (pos - 1); ++i) {
    if ((previous == nullptr) || (previous->next == nullptr)) {
      std::cout << "error head or pos!" << std::endl;
      return;
    } else {
      previous = previous->next;
    }
  }

  if (previous->next == nullptr) {
    std::cout << "error pos!" << std::endl;
    return;
  }

  LinkNode *temp = previous->next;
  previous->next = previous->next->next;
  delete temp;
  return;
}

void printList(const LinkNode *head) {
  const LinkNode *iter = head;
  while (iter != nullptr) {
    std::cout << iter->value << ", ";
    iter = iter->next;
  }
  std::cout << std::endl;
}

int main(int argc, char ** argv) {
  LinkNode *head = nullptr;
  for (int i = 0; i < 10; ++i) {
    insert(&head, i, i);
  }

  std::cout << "Before delete: ";
  printList(head);
  delete_node(&head, 5);
  std::cout << "After  delete: ";
  printList(head);
  return 0;
}
