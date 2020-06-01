// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

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
