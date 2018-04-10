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

# The Top CMake Script
#
# This project use Google Test as unit test framework, the code of this project follow Google C++
# Style Guide, in order to checking source files automatically, a custom target is created to call
# the lint tool "cpplint.py".

cmake_minimum_required(VERSION 3.9.3)
project(coding CXX)

# BUILD_SHARED_LIBS is a standard CMake variable, but we declare it here to make it prominent in the
# GUI. If it is set to ON, the libraries built by this project will preferable to be built as shared
# libraries.
option(BUILD_SHARED_LIBS "Build shared libraries (DLLs)." OFF)
# Define helper functions and macros.
include(utils/internal_utils.cmake)
fix_default_compiler_settings()  # Defined in internal_utils.cmake.

# Add Google Test as a subproject of our project.
add_subdirectory(gtest)
include_directories(gtest/googletest/include)

# In our project, we organize all source files of each target through CMake script files recursive
# including. Every directory with source files in it, must have a CMake script file "source.cmake",
# and each CMake script file(this file(CMakeLists.txt) no exception) should contain all its sub
# directory's "source.cmake" by "include" command.
include(${CMAKE_CURRENT_LIST_DIR}/src/source.cmake)

# Because source file list of each target, such as "UNIT_TEST_SOURCES", is defined in above CMake
# script files, so we must lay all commands which need source file list, such as "add_executable",
# bellow to any "include" command which aim to include "source.cmake".
