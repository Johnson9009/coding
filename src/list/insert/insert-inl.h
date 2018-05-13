// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#ifndef LIST_INSERT_INSERT_INL_H_
#define LIST_INSERT_INSERT_INL_H_

#include <stdexcept>

struct LinkNode {
  LinkNode(int var, LinkNode *next_node): value(var), next(next_node) {}
  int value;
  LinkNode * next;
};

void insert(LinkNode **head, int pos, int value) {
  if (head == nullptr) {
    throw std::invalid_argument("head");
  }

  if ((*head == nullptr) && (pos != 0)) {
    throw std::invalid_argument("empty:pos");
  } else if ((*head != nullptr) && (pos < 0)) {
    throw std::invalid_argument("nonempty:pos");
  }

  if (pos == 0) {
    *head = new LinkNode(value, *head);
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

  previous->next = new LinkNode(value, previous->next);
  return;
}

#endif  // LIST_INSERT_INSERT_INL_H_
