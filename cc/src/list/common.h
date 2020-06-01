// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#ifndef LIST_COMMON_H_
#define LIST_COMMON_H_

#include "gtest/gtest.h"

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

class OneNodeListTest : public ListTest {
 public:
  OneNodeListTest() : ListTest(1) {}
};

extern int const kMultiNodeCnt;

class MultiNodeListTest : public ListTest {
 public:
  MultiNodeListTest() : ListTest(kMultiNodeCnt) {}
};

class MultiNodeListParamTest : public testing::TestWithParam<int> {
 public:
  MultiNodeListParamTest() : head_(nullptr), original_length_(kMultiNodeCnt) {}
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

#endif  // LIST_COMMON_H_
