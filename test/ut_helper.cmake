# CMake function to imitate Bazel's cc_test rule.
#
# Parameters:
# NAME: name of target (see Usage below)
# SRCS: List of source files for the binary
# DEPS: List of other libraries to be linked in to the binary targets
#
# Note:
# By default, yy_test will always create a binary named yy_test_${NAME}.
# This will also add it to ctest list as yy_test_${NAME}.
#
# Usage:
# yy_test(
#   NAME
#     trader
#   SRCS
#     "trader_test1.cpp"
#     "trader_test2.cpp"
#   DEPS
#     gtest
#     gtest_main
# )

find_package(Threads REQUIRED)

include(GoogleTest)
function(yy_test)
  cmake_parse_arguments(YY_TEST
    ""
    "NAME"
    "SRCS;DEPS"
    ${ARGN}
  )

  set(_NAME "yy_test_${YY_TEST_NAME}")

  add_executable(${_NAME} "")
  target_sources(${_NAME} PRIVATE ${YY_TEST_SRCS})
  target_link_libraries(${_NAME} PUBLIC
    ${YY_TEST_DEPS}
    Threads::Threads
  )
  # Add all test executable to the unittest target folder.
  set_property(TARGET ${_NAME} PROPERTY FOLDER ${CMAKE_CURRENT_BINARY_DIR})

  gtest_discover_tests(${_NAME})
endfunction()
