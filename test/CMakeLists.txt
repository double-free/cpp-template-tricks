cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

# change name of project here
project(app LANGUAGES CXX)

# unittests
enable_testing()
include("ut_helper.cmake")


yy_test(
  NAME
    tuple
  SRCS
    TupleTests.cpp
  DEPS
    gtest
    gtest_main
)

yy_test(
  NAME
    variant
  SRCS
    VariantTests.cpp
  DEPS
    gtest
    gtest_main
)
