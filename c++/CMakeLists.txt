# Copyright (c) 2018-present, Johnson9009.
#
# This file is distributed under the MIT license. See the LICENSE file for details.

# The Top CMake Script
#
# This project use Google Test as unit test framework, the code of this project follow Google C++
# Style Guide, in order to checking source files automatically, a custom target is created to call
# the lint tool "cpplint.py".

cmake_minimum_required(VERSION 3.9)
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
