// Copyright (c) 2018-present, Johnson9009.
//
// This file is distributed under the MIT license. See the LICENSE file for details.

#ifndef GENERAL_ASSIGNMENT_OPERATOR_ASSIGNMENT_OPERATOR_H_
#define GENERAL_ASSIGNMENT_OPERATOR_ASSIGNMENT_OPERATOR_H_

#include <cstdio>
#include <cstring>

class String {
 public:
  explicit String(char const* str = nullptr);
  ~String(void);
  String(String const& str);
  String& operator=(String const& str);
  void Print();

 private:
  char* data_;
};

String& String::operator=(String const& str) {
  if (this == &str) return *this;
  int length = strlen(str.data_) + 1;
  char* new_data = new char[length];
  delete[] data_;
  data_ = new_data;
  snprintf(data_, length, "%s", str.data_);
  return *this;
}

#endif  // GENERAL_ASSIGNMENT_OPERATOR_ASSIGNMENT_OPERATOR_H_
