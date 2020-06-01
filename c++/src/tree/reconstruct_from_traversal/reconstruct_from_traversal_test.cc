// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#include "tree/reconstruct_from_traversal/reconstruct_from_traversal.h"

#include <cstdio>

void PrintTreeNode(const TreeNode* pNode) {
  if (pNode != nullptr) {
    printf("value of this node is: %d\n", pNode->value);

    if (pNode->left != nullptr)
      printf("value of its left child is: %d.\n", pNode->left->value);
    else
      printf("left child is nullptr.\n");

    if (pNode->right != nullptr)
      printf("value of its right child is: %d.\n", pNode->right->value);
    else
      printf("right child is nullptr.\n");
  } else {
    printf("this node is nullptr.\n");
  }

  printf("\n");
}

void PrintTree(const TreeNode* pRoot) {
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
void Test(char const* testName, int* preorder, int* inorder, int length) {
  if (testName != nullptr) printf("%s begins:\n", testName);

  printf("The preorder sequence is: ");
  for (int i = 0; i < length; ++i) printf("%d ", preorder[i]);
  printf("\n");

  printf("The inorder sequence is: ");
  for (int i = 0; i < length; ++i) printf("%d ", inorder[i]);
  printf("\n");

  try {
    TreeNode* root = ReconstructFromTraversal(preorder, inorder, length);
    PrintTree(root);

    DestroyTree(root);
  } catch (std::invalid_argument& ia) {
    printf("%s\n", ia.what());
  }
}

// 普通二叉树
//              1
//           /     \
//          2       3
//         /       / \
//        4       5   6
//         \         /
//          7       8
void Test1() {
  const int length = 8;
  int preorder[length] = {1, 2, 4, 7, 3, 5, 6, 8};
  int inorder[length] = {4, 7, 2, 1, 5, 3, 8, 6};

  Test("Test1", preorder, inorder, length);
}

// 所有结点都没有右子结点
//            1
//           /
//          2
//         /
//        3
//       /
//      4
//     /
//    5
void Test2() {
  const int length = 5;
  int preorder[length] = {1, 2, 3, 4, 5};
  int inorder[length] = {5, 4, 3, 2, 1};

  Test("Test2", preorder, inorder, length);
}

// 所有结点都没有左子结点
//            1
//             \
//              2
//               \
//                3
//                 \
//                  4
//                   \
//                    5
void Test3() {
  const int length = 5;
  int preorder[length] = {1, 2, 3, 4, 5};
  int inorder[length] = {1, 2, 3, 4, 5};

  Test("Test3", preorder, inorder, length);
}

// 树中只有一个结点
void Test4() {
  const int length = 1;
  int preorder[length] = {1};
  int inorder[length] = {1};

  Test("Test4", preorder, inorder, length);
}

// 完全二叉树
//              1
//           /     \
//          2       3
//         / \     / \
//        4   5   6   7
void Test5() {
  const int length = 7;
  int preorder[length] = {1, 2, 4, 5, 3, 6, 7};
  int inorder[length] = {4, 2, 5, 1, 6, 3, 7};

  Test("Test5", preorder, inorder, length);
}

// 输入空指针
void Test6() {
  Test("Test6", nullptr, nullptr, 0);
}

// 输入的两个序列不匹配
void Test7() {
  const int length = 7;
  int preorder[length] = {1, 2, 4, 5, 3, 6, 7};
  int inorder[length] = {4, 2, 8, 1, 6, 3, 7};

  Test("Test7: for unmatched input", preorder, inorder, length);
}

int main(int argc, char* argv[]) {
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
  Test6();
  Test7();

  return 0;
}
