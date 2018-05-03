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

class EmptyListTest : public ListTest {
 public:
  EmptyListTest() : ListTest(0) {}
};

#define EXPECT_THROW_STREQ(statement, expected_exception, expected_string) \
  do {                                                                  \
    try {                                                               \
      statement;                                                        \
      FAIL() << "Expected: " << #statement << " throws an exception of type " \
             << #expected_exception << "." << std::endl                 \
             << "  Actual: it throws nothing.";                         \
    } catch (expected_exception const &e) {                             \
      EXPECT_STREQ(expected_string, e.what());                          \
    } catch (...) {                                                     \
      FAIL() << "Expected: " << #statement << " throws an exception of type " \
             << #expected_exception << "." << std::endl                 \
             << "  Actual: it throws a different type.";                \
    }                                                                   \
  } while (false)

TEST_F(EmptyListTest, InvalidOperate) {
  ASSERT_EQ(nullptr, head_);
  for (auto pos : {-20, -1, 0, 1, 3}) {
    EXPECT_THROW_STREQ(delete_node(&head_, pos), std::invalid_argument, "head");
  }
}

class OneNodeListTest : public ListTest {
 public:
  OneNodeListTest() : ListTest(1) {}
};

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

#define MULTI_NODE_CNT 10

class MultiNodeListTest : public ListTest {
 public:
  MultiNodeListTest() : ListTest(MULTI_NODE_CNT) {}
};

// ASSERT_anything only can be used in functions whose return type is "void", because the method it
// used to break the execution of functions is return, so macro should be used in order to break the
// execution of test body.
#define CHECK_PARTIAL_LIST(node, first_value, count)  \
  do {                                                \
    for (int i = 0; i < count; ++i) {                 \
      ASSERT_NE(nullptr, node);                       \
      EXPECT_EQ(first_value + i, node->value);        \
      node = node->next;                              \
    }                                                 \
  } while (false)


TEST_F(MultiNodeListTest, PosEq0) {
  ASSERT_NE(nullptr, head_);
  delete_node(&head_, 0);
  LinkNode const *node = head_;
  CHECK_PARTIAL_LIST(node, 1, (original_length_ - 1));
  EXPECT_EQ(nullptr, node);
}

class MultiNodeListParamTest : public testing::TestWithParam<int> {
 public:
  MultiNodeListParamTest() : head_(nullptr), original_length_(MULTI_NODE_CNT) {}
 protected:
  virtual void SetUp() {
    ASSERT_EQ(nullptr, head_);
    ListTest::CreateList(&head_, original_length_);
  }
  virtual void TearDown() {
    ListTest::DestroyList(&head_);
  }
  LinkNode *head_;
  int original_length_;
};

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

INSTANTIATE_TEST_CASE_P(, MultiNodeListParamTest, testing::Range(1, MULTI_NODE_CNT));

TEST_F(MultiNodeListTest, InvalidPosLt0orGeLength) {
  ASSERT_NE(nullptr, head_);
  for (auto pos : {-23, -1, original_length_, original_length_ + 1, original_length_ + 3}) {
    EXPECT_THROW_STREQ(delete_node(&head_, pos), std::invalid_argument, "nonempty:pos");
  }
}
