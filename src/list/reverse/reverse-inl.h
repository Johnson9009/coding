// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#ifndef LIST_REVERSE_REVERSE_INL_H_
#define LIST_REVERSE_REVERSE_INL_H_

struct LinkNode {
  LinkNode(int var, LinkNode *next_node): value(var), next(next_node) {}
  int value;
  LinkNode * next;
};

void reverse(LinkNode **head) {
  if ((head == nullptr) || (*head == nullptr) || ((*head)->next == nullptr)) {
    return;
  }

  LinkNode *previous = *head;
  LinkNode *behind = (*head)->next->next;

  while (previous->next != nullptr) {
    previous->next->next = *head;
    *head = previous->next;
    previous->next = behind;
    if (behind != nullptr) {
      behind = behind->next;
    }
  }
  return;
}

#endif  // LIST_REVERSE_REVERSE_INL_H_
