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
