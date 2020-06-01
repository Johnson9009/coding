// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#include "list/insert/insert-inl.h"
#include "list/common.h"

TEST_F(EmptyListTest, PosEq0) {
  ASSERT_EQ(nullptr, head_);
  insert(&head_, 0, 807);
  ASSERT_NE(nullptr, head_);
  EXPECT_EQ(807, head_->value);
  EXPECT_EQ(nullptr, head_->next);
}

TEST_F(EmptyListTest, InvalidPosNe0) {
  ASSERT_EQ(nullptr, head_);
  for (auto pos : {-20, -1, 1, 3}) {
    EXPECT_THROW_STREQ(insert(&head_, pos, 808), std::invalid_argument, "empty:pos");
  }
}

TEST_F(OneNodeListTest, PosEq0) {
  ASSERT_NE(nullptr, head_);
  insert(&head_, 0, 809);
  ASSERT_NE(nullptr, head_);
  EXPECT_EQ(809, head_->value);
  LinkNode const *node = head_->next;
  ASSERT_NE(nullptr, node);
  EXPECT_EQ(0, node->value);
  EXPECT_EQ(nullptr, node->next);
}

TEST_F(OneNodeListTest, PosEqLength) {
  ASSERT_NE(nullptr, head_);
  insert(&head_, original_length_, 810);
  ASSERT_NE(nullptr, head_);
  EXPECT_EQ(0, head_->value);
  LinkNode const *inserted_node = head_->next;
  ASSERT_NE(nullptr, inserted_node);
  EXPECT_EQ(810, inserted_node->value);
  EXPECT_EQ(nullptr, inserted_node->next);
}

TEST_F(OneNodeListTest, InvalidPosLt0orGtLength) {
  ASSERT_NE(nullptr, head_);
  for (auto pos : {-23, -1, original_length_ + 1, original_length_ + 3}) {
    EXPECT_THROW_STREQ(insert(&head_, pos, 811), std::invalid_argument, "nonempty:pos");
  }
}

TEST_F(MultiNodeListTest, PosEq0) {
  ASSERT_NE(nullptr, head_);
  insert(&head_, 0, 812);
  ASSERT_NE(nullptr, head_);
  EXPECT_EQ(812, head_->value);
  LinkNode const *node = head_->next;
  CHECK_PARTIAL_LIST(node, 0, original_length_);
  EXPECT_EQ(nullptr, node);
}

TEST_P(MultiNodeListParamTest, PosGt0LtLength) {
  ASSERT_NE(nullptr, head_);
  int pos = GetParam();
  ASSERT_GT(pos, 0);
  ASSERT_LT(pos, original_length_);

  int insert_value = 813 + pos - 1;
  insert(&head_, pos, insert_value);
  LinkNode const *node = head_;
  CHECK_PARTIAL_LIST(node, 0, pos);
  LinkNode const *inserted_node = node;
  ASSERT_NE(nullptr, inserted_node);
  EXPECT_EQ(insert_value, inserted_node->value);
  node = inserted_node->next;
  CHECK_PARTIAL_LIST(node, pos, (original_length_ - pos));
  EXPECT_EQ(nullptr, node);
}

int const kMultiNodeCnt = 10;

INSTANTIATE_TEST_CASE_P(, MultiNodeListParamTest, testing::Range(1, kMultiNodeCnt));

TEST_F(MultiNodeListTest, PosEqLength) {
  ASSERT_NE(nullptr, head_);
  insert(&head_, original_length_, 814);
  LinkNode const *node = head_;
  CHECK_PARTIAL_LIST(node, 0, original_length_);
  LinkNode const *inserted_node = node;
  ASSERT_NE(nullptr, inserted_node);
  EXPECT_EQ(814, inserted_node->value);
  EXPECT_EQ(nullptr, inserted_node->next);
}

TEST_F(MultiNodeListTest, InvalidPosLt0orGtLength) {
  ASSERT_NE(nullptr, head_);
  for (auto pos : {-23, -1, original_length_ + 1, original_length_ + 3}) {
    EXPECT_THROW_STREQ(insert(&head_, pos, 815), std::invalid_argument, "nonempty:pos");
  }
}
