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

class EmptyListTest : public testing::Test {
 public:
  EmptyListTest() : head_(nullptr) {}
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
  static LinkNode const * GetNode(LinkNode const *head, int pos) {
    LinkNode const *node = head;
    for (int i = 0; i < pos; ++i) {
      if (node == nullptr) {
        return nullptr;
      }
      node = node->next;
    }
    return node;
  }

 protected:
  virtual void SetUp() {
    ASSERT_EQ(nullptr, head_);
    head_ = nullptr;
    return;
  }
  virtual void TearDown() {
    DestroyList(&head_);
    return;
  }
  LinkNode const * GetNode(int pos) const {
    return GetNode(head_, pos);
  }
  // If all tests are run serially, this variable can be static, because "SetUp" and "TearDown" can
  // ensure its consistency. But if all tests may be run in parallel, then this variable must not be
  // static.
  LinkNode *head_;
};

TEST_F(EmptyListTest, PosEq0) {
  ASSERT_EQ(nullptr, head_);
  insert(&head_, 0, 807);
  ASSERT_NE(nullptr, head_);
  EXPECT_EQ(807, head_->value);
  EXPECT_EQ(nullptr, head_->next);
}

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

TEST_F(EmptyListTest, InvalidPosNe0) {
  ASSERT_EQ(nullptr, head_);
  for (auto pos : {-20, -1, 1, 3}) {
    EXPECT_THROW_STREQ(insert(&head_, pos, 808), std::invalid_argument, "empty:pos");
  }
}

class NonEmptyListTest : public EmptyListTest {
 public:
  static int GetOriginalLength() {
    return original_length_;
  }
  static void CreateList(LinkNode **head) {
    LinkNode **node = head;
    for (int i = 0; i < original_length_; ++i) {
      *node = new LinkNode(i, nullptr);
      node = &((*node)->next);
    }
    return;
  }

 protected:
  virtual void SetUp() {
    ASSERT_EQ(nullptr, head_);
    CreateList(&head_);
  }
  static int original_length_;
};

int NonEmptyListTest::original_length_ = 10;

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

TEST_F(NonEmptyListTest, PosEq0) {
  ASSERT_NE(nullptr, head_);
  insert(&head_, 0, 809);
  ASSERT_NE(nullptr, head_);
  EXPECT_EQ(809, head_->value);
  LinkNode const *node = head_->next;
  CHECK_PARTIAL_LIST(node, 0, original_length_);
  EXPECT_EQ(nullptr, node);
}

class NonEmptyListParamTest : public testing::TestWithParam<int> {
 public:
  NonEmptyListParamTest() : head_(nullptr) {}
 protected:
  virtual void SetUp() {
    ASSERT_EQ(nullptr, head_);
    NonEmptyListTest::CreateList(&head_);
  }
  virtual void TearDown() {
    EmptyListTest::DestroyList(&head_);
  }
  LinkNode *head_;
};

TEST_P(NonEmptyListParamTest, PosGt0LtLength) {
  ASSERT_NE(nullptr, head_);
  int pos = GetParam();
  ASSERT_GT(pos, 0);
  ASSERT_LT(pos, NonEmptyListTest::GetOriginalLength());

  int insert_value = 810 + pos - 1;
  insert(&head_, pos, insert_value);
  LinkNode const *node = head_;
  CHECK_PARTIAL_LIST(node, 0, pos);
  LinkNode const *inserted_node = node;
  ASSERT_NE(nullptr, inserted_node);
  EXPECT_EQ(insert_value, inserted_node->value);
  node = inserted_node->next;
  CHECK_PARTIAL_LIST(node, pos, (NonEmptyListTest::GetOriginalLength() - pos));
  EXPECT_EQ(nullptr, node);
}

INSTANTIATE_TEST_CASE_P(, NonEmptyListParamTest,
                        testing::Range(1, NonEmptyListTest::GetOriginalLength()));

TEST_F(NonEmptyListTest, PosEqLength) {
  ASSERT_NE(nullptr, head_);
  insert(&head_, original_length_, 811);
  LinkNode const *node = head_;
  CHECK_PARTIAL_LIST(node, 0, original_length_);
  LinkNode const *inserted_node = node;
  ASSERT_NE(nullptr, inserted_node);
  EXPECT_EQ(811, inserted_node->value);
  EXPECT_EQ(nullptr, inserted_node->next);
}

TEST_F(NonEmptyListTest, InvalidPosLt0orGtLength) {
  ASSERT_NE(nullptr, head_);
  for (auto pos : {-23, -1, original_length_ + 1, original_length_ + 3}) {
    EXPECT_THROW_STREQ(insert(&head_, pos, 812), std::invalid_argument, "nonempty:pos");
  }
}
