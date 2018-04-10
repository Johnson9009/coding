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

# Define useful functions and macros.

include(CMakeParseArguments)
include(${CMAKE_CURRENT_LIST_DIR}/add_style_check.cmake)

# Tweaks CMake's default compiler/linker settings to suit needs of used libraries.
# This macro is modified from Google Test.
#
# This must be a macro(), as inside a function string() can only update variables in the function
# scope.
macro(fix_default_compiler_settings)
  if (MSVC)
    # For MSVC, CMake sets certain flags to defaults we want to override. This replacement code is
    # taken from sample in the CMake Wiki at http://www.cmake.org/Wiki/CMake_FAQ#Dynamic_Replace.
    foreach (flag_var
             CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL
             CMAKE_C_FLAGS_RELWITHDEBINFO CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG
             CMAKE_CXX_FLAGS_RELEASE CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
      if (NOT BUILD_SHARED_LIBS)
        # Generally shared libraries should use shared runtime libraries(CRT), and executable who
        # use these shared libraries should also use shared CRT. Otherwise, it may end up with
        # multiple copies of runtime library data in different modules, resulting in hard-to-find
        # crashes. Static libraries are preferable to use static CRT, as we don't have to rely on
        # CRT DLLs being available, similarly the executable who use these static libraries should
        # also use static CRT. CMake always defaults to using shared CRT libraries, so we override
        # that default here.
        string(REPLACE "/MD" "-MT" ${flag_var} "${${flag_var}}")
      endif()

      # We prefer more strict warning checking, so replace /W3 with /W4 in defaults.
      string(REPLACE "/W3" "/W4" ${flag_var} "${${flag_var}}")
    endforeach()
  endif()
endmacro()

# Every directory with source files in it, must have a CMake script file such as "source.cmake",
# with help of macro "get_src_list_of_each_target", "source.cmake" file only need to give a
# description of the relationship between targets and source files that inside current directory,
# needn't contain its all sub directory's "source.cmake" by "include" command. All "source.cmake"
# files will be included at the caller place. Just as CMake document says "We do not recommend
# using GLOB to collect a list of source files from your source tree. If no CMakeLists.txt file
# changes when a source is added or removed then the generated build system cannot know when to ask
# CMake to regenerate.", macro "get_src_list_of_each_target" have the same problem.
macro(get_src_list_of_each_target source_files_descriptor)
  file(GLOB_RECURSE source_cmakes LIST_DIRECTORIES false ${source_files_descriptor})
  foreach (source_cmake ${source_cmakes})
    include(${source_cmake})
  endforeach()
endmacro()
