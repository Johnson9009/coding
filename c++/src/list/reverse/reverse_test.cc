// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#include "list/reverse/reverse-inl.h"
#include "list/common.h"

TEST(CrashTest, HeadNodeNotExist) {
  reverse(nullptr);
}

TEST(CrashTest, EmptyList) {
  LinkNode *head = nullptr;
  reverse(&head);
  ASSERT_EQ(nullptr, head);
}

TEST_F(OneNodeListTest, All) {
  ASSERT_NE(nullptr, head_);
  reverse(&head_);
  ASSERT_NE(nullptr, head_);
  EXPECT_EQ(0, head_->value);
  EXPECT_EQ(nullptr, head_->next);
}

int const kMultiNodeCnt = 10;

TEST_F(MultiNodeListTest, All) {
  ASSERT_NE(nullptr, head_);
  reverse(&head_);
  LinkNode const *node = head_;
  for (int i = (original_length_ - 1); i >= 0; --i) {
    ASSERT_NE(nullptr, node);
    EXPECT_EQ(i, node->value);
    node = node->next;
  }
  EXPECT_EQ(nullptr, node);
}
