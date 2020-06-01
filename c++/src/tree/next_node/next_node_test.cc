// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#include "tree/next_node/next_node.h"

#include <cstdio>

// ==================== 辅助代码用来构建二叉树 ====================
TreeNode* CreateTreeNode(int value) {
  TreeNode* pNode = new TreeNode();
  pNode->value = value;
  pNode->left = nullptr;
  pNode->right = nullptr;
  pNode->parent = nullptr;

  return pNode;
}

void ConnectTreeNodes(TreeNode* pParent, TreeNode* pLeft, TreeNode* pRight) {
  if (pParent != nullptr) {
    pParent->left = pLeft;
    pParent->right = pRight;

    if (pLeft != nullptr) pLeft->parent = pParent;
    if (pRight != nullptr) pRight->parent = pParent;
  }
}

void PrintTreeNode(TreeNode* pNode) {
  if (pNode != nullptr) {
    printf("value of this node is: %d\n", pNode->value);

    if (pNode->left != nullptr)
      printf("value of its left child is: %d.\n", pNode->left->value);
    else
      printf("left child is null.\n");

    if (pNode->right != nullptr)
      printf("value of its right child is: %d.\n", pNode->right->value);
    else
      printf("right child is null.\n");
  } else {
    printf("this node is null.\n");
  }

  printf("\n");
}

void PrintTree(TreeNode* pRoot) {
  PrintTreeNode(pRoot);

  if (pRoot != nullptr) {
    if (pRoot->left != nullptr) PrintTree(pRoot->left);

    if (pRoot->right != nullptr) PrintTree(pRoot->right);
  }
}

void DestroyTree(TreeNode* pRoot) {
  if (pRoot != nullptr) {
    TreeNode* pLeft = pRoot->left;
    TreeNode* pRight = pRoot->right;

    delete pRoot;
    pRoot = nullptr;

    DestroyTree(pLeft);
    DestroyTree(pRight);
  }
}

// ====================测试代码====================
void Test(char const* testName, TreeNode* pNode, TreeNode* expected) {
  if (testName != nullptr) printf("%s begins: ", testName);

  TreeNode* pNext = GetNextNodeOfInOrder(pNode);
  if (pNext == expected)
    printf("Passed.\n");
  else
    printf("FAILED.\n");
}

//            8
//        6      10
//       5 7    9  11
void Test1_7() {
  TreeNode* pNode8 = CreateTreeNode(8);
  TreeNode* pNode6 = CreateTreeNode(6);
  TreeNode* pNode10 = CreateTreeNode(10);
  TreeNode* pNode5 = CreateTreeNode(5);
  TreeNode* pNode7 = CreateTreeNode(7);
  TreeNode* pNode9 = CreateTreeNode(9);
  TreeNode* pNode11 = CreateTreeNode(11);

  ConnectTreeNodes(pNode8, pNode6, pNode10);
  ConnectTreeNodes(pNode6, pNode5, pNode7);
  ConnectTreeNodes(pNode10, pNode9, pNode11);

  Test("Test1", pNode8, pNode9);
  Test("Test2", pNode6, pNode7);
  Test("Test3", pNode10, pNode11);
  Test("Test4", pNode5, pNode6);
  Test("Test5", pNode7, pNode8);
  Test("Test6", pNode9, pNode10);
  Test("Test7", pNode11, nullptr);

  DestroyTree(pNode8);
}

//            5
//          4
//        3
//      2
void Test8_11() {
  TreeNode* pNode5 = CreateTreeNode(5);
  TreeNode* pNode4 = CreateTreeNode(4);
  TreeNode* pNode3 = CreateTreeNode(3);
  TreeNode* pNode2 = CreateTreeNode(2);

  ConnectTreeNodes(pNode5, pNode4, nullptr);
  ConnectTreeNodes(pNode4, pNode3, nullptr);
  ConnectTreeNodes(pNode3, pNode2, nullptr);

  Test("Test8", pNode5, nullptr);
  Test("Test9", pNode4, pNode5);
  Test("Test10", pNode3, pNode4);
  Test("Test11", pNode2, pNode3);

  DestroyTree(pNode5);
}

//        2
//         3
//          4
//           5
void Test12_15() {
  TreeNode* pNode2 = CreateTreeNode(2);
  TreeNode* pNode3 = CreateTreeNode(3);
  TreeNode* pNode4 = CreateTreeNode(4);
  TreeNode* pNode5 = CreateTreeNode(5);

  ConnectTreeNodes(pNode2, nullptr, pNode3);
  ConnectTreeNodes(pNode3, nullptr, pNode4);
  ConnectTreeNodes(pNode4, nullptr, pNode5);

  Test("Test12", pNode5, nullptr);
  Test("Test13", pNode4, pNode5);
  Test("Test14", pNode3, pNode4);
  Test("Test15", pNode2, pNode3);

  DestroyTree(pNode2);
}

void Test16() {
  TreeNode* pNode5 = CreateTreeNode(5);

  Test("Test16", pNode5, nullptr);

  DestroyTree(pNode5);
}

int main(int argc, char* argv[]) {
  Test1_7();
  Test8_11();
  Test12_15();
  Test16();
}
