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

#include "list/delete/delete-inl.h"
#include "list/common.h"

TEST_F(EmptyListTest, InvalidOperate) {
  ASSERT_EQ(nullptr, head_);
  for (auto pos : {-20, -1, 0, 1, 3}) {
    EXPECT_THROW_STREQ(delete_node(&head_, pos), std::invalid_argument, "head");
  }
}

TEST_F(OneNodeListTest, PosEq0) {
  ASSERT_NE(nullptr, head_);
  delete_node(&head_, 0);
  EXPECT_EQ(nullptr, head_);
}

TEST_F(OneNodeListTest, InvalidPosNe0) {
  ASSERT_NE(nullptr, head_);
  for (auto pos : {-23, -1, 1, 4}) {
    EXPECT_THROW_STREQ(delete_node(&head_, pos), std::invalid_argument, "nonempty:pos");
  }
}

TEST_F(MultiNodeListTest, PosEq0) {
  ASSERT_NE(nullptr, head_);
  delete_node(&head_, 0);
  LinkNode const *node = head_;
  CHECK_PARTIAL_LIST(node, 1, (original_length_ - 1));
  EXPECT_EQ(nullptr, node);
}

TEST_P(MultiNodeListParamTest, PosGt0LtLength) {
  ASSERT_NE(nullptr, head_);
  int pos = GetParam();
  ASSERT_GT(pos, 0);
  ASSERT_LT(pos, original_length_);

  delete_node(&head_, pos);
  LinkNode const *node = head_;
  CHECK_PARTIAL_LIST(node, 0, pos);
  CHECK_PARTIAL_LIST(node, (pos + 1), (original_length_ - pos - 1));
  EXPECT_EQ(nullptr, node);
}

int const kMultiNodeCnt = 10;

INSTANTIATE_TEST_CASE_P(, MultiNodeListParamTest, testing::Range(1, kMultiNodeCnt));

TEST_F(MultiNodeListTest, InvalidPosLt0orGeLength) {
  ASSERT_NE(nullptr, head_);
  for (auto pos : {-23, -1, original_length_, original_length_ + 1, original_length_ + 3}) {
    EXPECT_THROW_STREQ(delete_node(&head_, pos), std::invalid_argument, "nonempty:pos");
  }
}
