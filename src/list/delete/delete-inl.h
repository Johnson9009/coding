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

#ifndef LIST_DELETE_DELETE_INL_H_
#define LIST_DELETE_DELETE_INL_H_

#include <stdexcept>

struct LinkNode {
  LinkNode(int var, LinkNode *next_node): value(var), next(next_node) {}
  int value;
  LinkNode * next;
};

void delete_node(LinkNode **head, int pos) {
  if ((head == nullptr) || (*head == nullptr)) {
    throw std::invalid_argument("head");
  }

  if (pos < 0) {
    throw std::invalid_argument("nonempty:pos");
  }

  if (pos == 0) {
    LinkNode *temp = *head;
    *head = (*head)->next;
    delete temp;
    return;
  }

  LinkNode *previous = *head;
  for (int i = 0; i < (pos - 1); ++i) {
    if (previous->next == nullptr) {
      throw std::invalid_argument("nonempty:pos");
    } else {
      previous = previous->next;
    }
  }

  if (previous->next == nullptr) {
    throw std::invalid_argument("nonempty:pos");
  }

  LinkNode *temp = previous->next;
  previous->next = previous->next->next;
  delete temp;
  return;
}

#endif  // LIST_DELETE_DELETE_INL_H_
