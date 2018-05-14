// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#include "general/assignment_operator/assignment_operator.h"

String::String(char const* pData) {
  if (pData == nullptr) {
    data_ = new char[1];
    data_[0] = '\0';
  } else {
    int length = strlen(pData);
    data_ = new char[length + 1];
    snprintf(data_, length + 1, "%s", pData);
  }
}

String::String(const String& str) {
  int length = strlen(str.data_);
  data_ = new char[length + 1];
  snprintf(data_, length + 1, "%s", str.data_);
}

String::~String() {
  delete[] data_;
}

// ====================测试代码====================
void String::Print() {
  printf("%s", data_);
}

void Test1() {
  printf("Test1 begins:\n");

  char const* text = "Hello world";

  String str1(text);
  String str2;
  str2 = str1;

  printf("The expected result is: %s.\n", text);

  printf("The actual result is: ");
  str2.Print();
  printf(".\n");
}

// 赋值给自己
void Test2() {
  printf("Test2 begins:\n");

  char const* text = "Hello world";

  String str1(text);
  str1 = str1;

  printf("The expected result is: %s.\n", text);

  printf("The actual result is: ");
  str1.Print();
  printf(".\n");
}

// 连续赋值
void Test3() {
  printf("Test3 begins:\n");

  char const* text = "Hello world";

  String str1(text);
  String str2, str3;
  str3 = str2 = str1;

  printf("The expected result is: %s.\n", text);

  printf("The actual result is: ");
  str2.Print();
  printf(".\n");

  printf("The expected result is: %s.\n", text);

  printf("The actual result is: ");
  str3.Print();
  printf(".\n");
}

int main(int argc, char* argv[]) {
  Test1();
  Test2();
  Test3();

  return 0;
}
