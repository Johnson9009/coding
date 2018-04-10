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

# Add style check to a target, it only support Google C++ Style Guide check tool "cpplint.py" now.

include(CMakeParseArguments)

cmake_policy(SET CMP0011 NEW)
if(POLICY CMP0054)
  cmake_policy(SET CMP0054 NEW)
endif()

# add_style_check(<target_name>
#   [EXCLUDE_DIRS <exclude_dir> [<exclude_dir> ...]]
#   [EXCLUDE_FILES <exclude_file> [<exclude_file> ...]]
# )
# This function can get all header files used by source files of target automatically, default
# files that need to be check is comprised of all source files and header files of this target,
# system header files will be exclude directly.
function(add_style_check target_name)
  assert_cpplint_available()
  # Parse arguments to corresponding varialbes.
  set(multi_value_args EXCLUDE_DIRS EXCLUDE_FILES)
  cmake_parse_arguments(arg "" "" "${multi_value_args}" ${ARGN})

  if (NOT TARGET ${target_name})
    message(FATAL_ERROR "Can't find the target which named \"${target_name}\"!")
  endif()

  # Convert relative path to absolute path and assert the exist of each folder and file.
  foreach (exclude_dir ${arg_EXCLUDE_DIRS})
    get_filename_component(exclude_dir ${exclude_dir} ABSOLUTE)
    if (NOT EXISTS ${exclude_dir})
      message(FATAL_ERROR "Can't find the folder: \"${exclude_dir}\"!")
    else()
      set(exclude_dirs ${exclude_dirs} ${exclude_dir})
    endif()
  endforeach()
  foreach (exclude_file ${arg_EXCLUDE_FILES})
    get_filename_component(exclude_file ${exclude_file} ABSOLUTE)
    if (NOT EXISTS ${exclude_file})
      message(FATAL_ERROR "Can't find the file: \"${exclude_file}\"!")
    else()
      set(exclude_files ${exclude_files} ${exclude_file})
    endif()
  endforeach()
                # message("exclude_dirs is ${exclude_dirs}")  # Debug use.
                # message("exclude_files is ${exclude_files}")  # Debug use.
  # Get include directories and source files of target, and convert relative path to absolute path
  # and assert the exist of each include directory and source file.
  get_target_property(arg_src_files ${target_name} SOURCES)
  if (NOT arg_src_files)
    message(FATAL_ERROR "Target must have one source file at least!")
  else()
    foreach (src_file ${arg_src_files})
      get_filename_component(src_file ${src_file} ABSOLUTE)
      if (NOT EXISTS ${src_file})
        message(FATAL_ERROR "Can't find the file: \"${src_file}\"!")
      else()
        set(src_files ${src_files} ${src_file})
      endif()
    endforeach()
    list(REMOVE_DUPLICATES src_files)
  endif()

  get_target_property(compile_defines ${target_name} COMPILE_DEFINITIONS)
  if (NOT compile_defines)
    unset(compile_defines)
  else()
    list(REMOVE_DUPLICATES compile_defines)
  endif()

  get_target_property(arg_include_dirs ${target_name} INCLUDE_DIRECTORIES)
  if (NOT arg_include_dirs)
    unset(arg_include_dirs)
  else()
    foreach (include_dir ${arg_include_dirs})
      get_filename_component(include_dir ${include_dir} ABSOLUTE)
      if (NOT EXISTS ${include_dir})
        message(FATAL_ERROR "Can't find the folder: \"${include_dir}\"!")
      else()
        set(include_dirs ${include_dirs} ${include_dir})
      endif()
    endforeach()
    list(REMOVE_DUPLICATES include_dirs)
  endif()
                # message("include_dirs is ${include_dirs}") # Debug use.
                # message("compile_defines is ${compile_defines}") # Debug use.
                # message("src_files is ${src_files}") # Debug use.
  # Get all header files used in this target through compiler.
  get_dependent_header_files(raw_header_files
    SRC_FILES ${src_files}
    COMPILE_DEFINES ${compile_defines}
    INCLUDE_DIRS  ${include_dirs}
  )

                # message("raw_header_files is ${raw_header_files}") # Debug use.
  # Strip white characters and assert the exist of each header file, then remove duplicate items.
  foreach(header_file ${raw_header_files})
    string(STRIP ${header_file} header_file)
    if (NOT EXISTS ${header_file})
      message(FATAL_ERROR "Can't find the header file: \"${header_file}\", function\
      \"add_style_check\" find it is used by target \"${target_name}\"!")
    else()
      set(header_files ${header_files} ${header_file})
    endif()
  endforeach()
  if (header_files)
    list(REMOVE_DUPLICATES header_files)
  endif()

                # message("header_files is ${header_files}") # Debug use.
  # Remove the files that under exclude directories or in exclude file list.
  set(files ${src_files} ${header_files})
  list(REMOVE_DUPLICATES files)
  foreach (exclude_dir ${exclude_dirs})
    foreach (file_name ${files})
      string(REGEX MATCHALL "${exclude_dir}.*" need_remove ${file_name})
      if (need_remove)
        list(REMOVE_ITEM files ${file_name})
      endif()
    endforeach()
  endforeach()
  foreach (exclude_file ${exclude_files})
    list(REMOVE_ITEM files ${exclude_file})
  endforeach()
                # message("files is ${files}") # Debug use.
  add_custom_command(TARGET ${target_name} PRE_LINK
    COMMAND "${PYTHON_EXECUTABLE}" "${CPPLINT_PY}" --linelength=100 --root=include ${files}
    COMMENT "Linting ${target_name}"
    VERBATIM)
endfunction()


macro(assert_cpplint_available)
  if (NOT PYTHONINTERP_FOUND)
    # Sets PYTHONINTERP_FOUND and PYTHON_EXECUTABLE.
    find_package(PythonInterp)
    if (NOT PYTHONINTERP_FOUND)
      message(FATAL_ERROR "Can't find python interpreter!")
    endif()
  endif()

  if (NOT CPPLINT_PY)
    find_file(CPPLINT_PY cpplint.py ${CMAKE_HOME_DIRECTORY}/utils)
    if (NOT CPPLINT_PY)
      message(FATAL_ERROR "Can't find \"Google C++ Style Guide\" lint tool \"cpplint.py\"!")
    endif()
  endif()
endmacro()

function(get_dependent_header_files header_files)
  # Parse arguments to corresponding varialbes.
  set(multi_value_args SRC_FILES COMPILE_DEFINES INCLUDE_DIRS)
  cmake_parse_arguments(arg "" "" "${multi_value_args}" ${ARGN})

  # Separate C source files from C++ source files.
  foreach (src_file ${arg_SRC_FILES})
    get_source_file_property(language_type ${src_file} LANGUAGE)
    if ("${language_type}" STREQUAL "C")
      set(c_src_files ${c_src_files} ${src_file})
    elseif ("${language_type}" STREQUAL "CXX")
      set(cxx_src_files ${cxx_src_files} ${src_file})
    else()
      message(FATAL_ERROR "Can't process neither C nor C++ source file: \"${src_file}\"!")
    endif()
  endforeach()
                # message("CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}") # Debug use.
  # Set compile flags according to build type.
  if (NOT CMAKE_BUILD_TYPE)
    set(c_compile_flags "${CMAKE_C_FLAGS}")
    set(cxx_compile_flags "${CMAKE_CXX_FLAGS}")
  else()
    string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)
    if ("${build_type}" STREQUAL "debug")
      set(c_compile_flags "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG} -D_DEBUG")
      set(cxx_compile_flags "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")
    elseif ("${build_type}" STREQUAL "release")
      set(c_compile_flags "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}")
      set(cxx_compile_flags "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}")
    elseif ("${build_type}" STREQUAL "relwithdebinfo")
      set(c_compile_flags "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELWITHDEBINFO}")
      set(cxx_compile_flags "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
    elseif ("${build_type}" STREQUAL "minsizerel")
      set(c_compile_flags "${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_MINSIZEREL}")
      set(cxx_compile_flags "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_MINSIZEREL}")
    else()
      set(c_compile_flags "${CMAKE_C_FLAGS}")
      set(cxx_compile_flags "${CMAKE_CXX_FLAGS}")
      message(WARNING "You are using custom build type ${CMAKE_BUILD_TYPE}, compile definitions in\
   CMAKE_C_FLAGS and CMAKE_CXX_FLAGS will be used!")
    endif()
  endif()

  if (c_compile_flags)
    string(REGEX MATCHALL "(/|-)D[^ ]*" c_compile_flags ${c_compile_flags})
    foreach(c_default_define ${c_compile_flags})
      string(REGEX REPLACE "(/|-)D" "" c_default_define ${c_default_define})
      set(c_default_defines ${c_default_defines} ${c_default_define})
    endforeach()
    list(REMOVE_DUPLICATES c_default_defines)
  endif()
  if (cxx_compile_flags)
    string(REGEX MATCHALL "(/|-)D[^ ]*" cxx_compile_flags ${cxx_compile_flags})
    foreach(cxx_default_define ${cxx_compile_flags})
      string(REGEX REPLACE "(/|-)D" "" cxx_default_define ${cxx_default_define})
      set(cxx_default_defines ${cxx_default_defines} ${cxx_default_define})
    endforeach()
    list(REMOVE_DUPLICATES cxx_default_defines)
  endif()

  # Get dependent header files of C and C++ source files separately, then combine them together.
  if (c_src_files)
    get_header_files_by_compiler(c_header_files ${CMAKE_C_COMPILER} ${CMAKE_C_COMPILER_ID}
      SRC_FILES        ${c_src_files}
      COMPILE_DEFINES  ${c_default_defines} ${arg_COMPILE_DEFINES}
      INCLUDE_DIRS     ${arg_INCLUDE_DIRS}
    )
  elseif (cxx_src_files)
    get_header_files_by_compiler(cxx_header_files ${CMAKE_CXX_COMPILER} ${CMAKE_CXX_COMPILER_ID}
      SRC_FILES        ${cxx_src_files}
      COMPILE_DEFINES  ${cxx_default_defines} ${arg_COMPILE_DEFINES}
      INCLUDE_DIRS     ${arg_INCLUDE_DIRS}
    )
  else()
    message(FATAL_ERROR "There isn't any C or C++ source file!")
  endif()

  set(${header_files} ${c_header_files} ${cxx_header_files} PARENT_SCOPE)
endfunction()

function(get_header_files_by_compiler header_files compiler compiler_id)
  # Parse arguments to corresponding varialbes.
  set(multi_value_args SRC_FILES COMPILE_DEFINES INCLUDE_DIRS)
  cmake_parse_arguments(arg "" "" "${multi_value_args}" ${ARGN})

  # Select correct compiler flags, and assume the compiler is GNU by default.
  set(definition_flag "-D")
  set(include_dir_flag "-I")
  set(list_header_files_flag "-MM")
  if ("${compiler_id}" STREQUAL "MSVC")
    if ("$ENV{INCLUDE}" STREQUAL "")
      message(FATAL_ERROR "To use the function \"add_style_check\" with Visual C++, cmake must be\
        run from a shell that can use the compiler cl from the command line, and the \"INCLUDE\"\
        environment variable must be set correctly. To fix this problem, run cmake from the Visual \
        Studio Command Prompt (vcvarsall.bat).")
    else()
      set(definition_flag "/D")
      set(include_dir_flag "/I")
      set(list_header_files_flag "/showIncludes")
    endif()
  elseif (NOT (("${compiler_id}" STREQUAL "Clang") OR
               ("${compiler_id}" STREQUAL "AppleClang") OR
               ("${compiler_id}" STREQUAL "GNU")))
    message(FATAL_ERROR "Can't support your compiler ${compiler_id} now, only MSVC, Clang, AppleClang, GNU compiler can be used!")
  endif()

  # Add compiler flags for each of compile definitions and include directories.
  foreach (compile_define ${arg_COMPILE_DEFINES})
    set(compile_defines_line ${compile_defines_line} ${definition_flag} ${compile_define})
  endforeach()
  foreach (include_dir ${arg_INCLUDE_DIRS})
    set(include_dirs_line ${include_dirs_line} ${include_dir_flag} ${include_dir})
  endforeach()

  execute_process(
    COMMAND ${compiler} ${compile_defines_line} ${include_dirs_line}
                        ${list_header_files_flag} ${arg_SRC_FILES}
    OUTPUT_VARIABLE stdout
    ERROR_VARIABLE  stderr
  )

  # Filter the stdout and get the dependent header files only inside the specific include
  # directories , then put the result to the caller.
                # message("stdout is ${stdout}")  # Debug use.
  foreach (include_dir ${arg_INCLUDE_DIRS})
    string(REGEX MATCHALL "${include_dir}[\\/][^\\\n]*" filter_result ${stdout})
    set(filter_results ${filter_results} ${filter_result})
  endforeach()
                # message("filter_results is ${filter_results}")  # Debug use.
  set(${header_files} ${filter_results} PARENT_SCOPE)
endfunction()
