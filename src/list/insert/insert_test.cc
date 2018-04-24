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

#include "list/insert/insert-inl.h"

#include "gtest/gtest.h"

class InsertList : public testing::Test {
 protected:
  static void SetUpTestCase() {
    head_ = nullptr;
  }
  static void TearDownTestCase() {
    LinkNode *node = head_;
    while (node != nullptr) {
      LinkNode *temp = node;
      node = node->next;
      delete temp;
    }
    head_ = nullptr;
  }
  static LinkNode *head_;
};

LinkNode *InsertList::head_ = nullptr;

TEST_F(InsertList, SequenceFromHead) {
  for (int i = 0; i < 10; ++i) {
    insert(&head_, i, i);
  }

  LinkNode *node = head_;
  for (int i = 0; i < 10; ++i) {
    EXPECT_EQ(i, node->value);
    node = node->next;
  }
}
