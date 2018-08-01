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

  LinkNode* cur_head = *head;
  LinkNode* ahead = *head;
  LinkNode* behind = (*head)->next->next;

  while (ahead->next != nullptr) {
    ahead->next->next = cur_head;
    cur_head = ahead->next;
    ahead->next = behind;
    if (behind != nullptr) {
      behind = behind->next;
    }
  }
  *head = cur_head;
  return;
}

#endif  // LIST_REVERSE_REVERSE_INL_H_
