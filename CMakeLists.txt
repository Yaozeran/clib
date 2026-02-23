cmake_minimum_required(VERSION 3.20)

project(clib)

add_library(ds INTERFACE
  src/ds/list.h
  src/ds/tree.h
)
target_compile_features(ds INTERFACE cxx_std_20)

add_library(algo 
  src/algo/leetcode.cc
)
target_compile_features(algo PUBLIC cxx_std_20)
target_include_directories(algo PUBLIC ./src)

add_executable(test_ds_list ./test/ds/list.cc)
target_link_libraries(test_ds_list
  PRIVATE ds)
target_include_directories(test_ds_list PRIVATE ./src)