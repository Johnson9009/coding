// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

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
