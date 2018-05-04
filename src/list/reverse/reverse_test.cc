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

#include "gtest/gtest.h"

class ListTest : public testing::Test {
 public:
  explicit ListTest(int length) : head_(nullptr), original_length_(length) {}
  static void CreateList(LinkNode **head, int length) {
    LinkNode **node = head;
    for (int i = 0; i < length; ++i) {
      *node = new LinkNode(i, nullptr);
      node = &((*node)->next);
    }
    return;
  }
  static void DestroyList(LinkNode **head) {
    LinkNode *node = *head;
    while (node != nullptr) {
      LinkNode *temp = node;
      node = node->next;
      delete temp;
    }
    *head = nullptr;
    return;
  }

 protected:
  virtual void SetUp() {
    ASSERT_EQ(nullptr, head_);
    CreateList(&head_, original_length_);
  }
  virtual void TearDown() {
    DestroyList(&head_);
    return;
  }
  // If all tests are run serially, this variable can be static, because "SetUp" and "TearDown" can
  // ensure its consistency. But if all tests may be run in parallel, then this variable must not be
  // static.
  LinkNode *head_;
  int original_length_;
};

TEST(CrashTest, HeadNodeNotExist) {
  reverse(nullptr);
}

TEST(CrashTest, EmptyList) {
  LinkNode *head = nullptr;
  reverse(&head);
  ASSERT_EQ(nullptr, head);
}

class OneNodeListTest : public ListTest {
 public:
  OneNodeListTest() : ListTest(1) {}
};

TEST_F(OneNodeListTest, All) {
  ASSERT_NE(nullptr, head_);
  reverse(&head_);
  ASSERT_NE(nullptr, head_);
  EXPECT_EQ(0, head_->value);
  EXPECT_EQ(nullptr, head_->next);
}

int const kMultiNodeCnt = 10;

class MultiNodeListTest : public ListTest {
 public:
  MultiNodeListTest() : ListTest(kMultiNodeCnt) {}
};

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
