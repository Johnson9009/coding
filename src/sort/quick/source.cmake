# Copyright (c) 2016 Johnson9009. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
# associated documentation files(the "Software"), to deal in the Software without restriction,
# including without limitation the rights to use, copy, modify, merge, publish, distribute,
# sublicense, and / or sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions :
#
# The above copyright notice and this permission notice shall be included in all copies or
# substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
# NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
# DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT
# OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

# Every directory with source files in it, must have this cmake script file, at the top of this file
# must contain all its sub directory's "source.cmake" by "include" command. If current directory or
# its any sub directories need to be added into include directories by "include_directories"
# command, then all the "include_directories" commands must be placed above any "include" command,
# and any other commands must be placed below all "include" commands. This file only need to give a
# description of the relationship between targets and source files that inside current directory.

set(SORT_QUICK_SRCS ${SORT_QUICK_SRCS}
    ${CMAKE_CURRENT_LIST_DIR}/quick.cc
)

# Because source file list of each target, such as "UNIT_TEST_SOURCES", is defined in above CMake
# script files, so we must lay all commands which need source file list, such as "add_executable",
# bellow to any "include" command which aim to include "source.cmake".
add_executable(sort_quick ${SORT_QUICK_SRCS})
target_link_libraries(sort_quick gtest_main)
# PRIVATE: Target requires some compile features only when it is built itself, but its consumers are
# not required to use a compiler which supports these features.
# PUBLIC or INTERFACE: The interface of target require some compile features.
target_compile_features(sort_quick PRIVATE cxx_std_11)
add_style_check(sort_quick
  EXCLUDE_DIRS gtest
)
