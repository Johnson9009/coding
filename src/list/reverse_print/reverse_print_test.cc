// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#include "list/reverse_print/reverse_print.h"

// ====================测试代码====================
void PrintList(LinkNode* pHead) {
  printf("PrintList starts.\n");

  LinkNode* pNode = pHead;
  while (pNode != nullptr) {
    printf("%d\t", pNode->value);
    pNode = pNode->next;
  }

  printf("\nPrintList ends.\n");
}

void DestroyList(LinkNode* pHead) {
  LinkNode* pNode = pHead;
  while (pNode != nullptr) {
    pHead = pHead->next;
    delete pNode;
    pNode = pHead;
  }
}

void Test(LinkNode* pHead) {
  PrintList(pHead);
  ReversePrintNoEditIteratively(pHead);
  printf("\n");
  ReversePrintNoEditRecursively(pHead);
  printf("\n");
  ReversePrint(pHead);
}

// 1->2->3->4->5
void Test1() {
  printf("\nTest1 begins.\n");

  LinkNode* pNode5 = new LinkNode(5, nullptr);
  LinkNode* pNode4 = new LinkNode(4, pNode5);
  LinkNode* pNode3 = new LinkNode(3, pNode4);
  LinkNode* pNode2 = new LinkNode(2, pNode3);
  LinkNode* pNode1 = new LinkNode(1, pNode2);

  Test(pNode1);

  DestroyList(pNode1);
}

// 只有一个结点的链表: 1
void Test2() {
  printf("\nTest2 begins.\n");

  LinkNode* pNode1 = new LinkNode(1, nullptr);

  Test(pNode1);

  DestroyList(pNode1);
}

// 空链表
void Test3() {
  printf("\nTest3 begins.\n");

  Test(nullptr);
}

int main(int argc, char* argv[]) {
  Test1();
  Test2();
  Test3();

  return 0;
}
