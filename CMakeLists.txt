# Copyright (c) 2026 Yao Zeran

cmake_minimum_required(VERSION 3.20)

project(clib)

# data structure lib

add_library(ds INTERFACE
  src/ds/list.h
  src/ds/tree.h
)
target_compile_features(ds INTERFACE cxx_std_20)

# io serialization and deserialization lib

add_library(serdes INTERFACE
  src/io/serdes/include.h
)
target_include_directories(serdes INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/io/serdes
)
target_compile_features(serdes INTERFACE cxx_std_23)

# algorithms

add_library(algo 
  src/algo/leetcode.cc
)
target_compile_features(algo PUBLIC cxx_std_20)
target_include_directories(algo PUBLIC ./src)

# net

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/net
)

# executables

add_executable(test_ds_list ./test/ds/list.cc)
target_link_libraries(test_ds_list
  PRIVATE ds)
target_include_directories(test_ds_list PRIVATE ./src)

add_executable(test_io ./test/io/main.cc)
target_link_libraries(test_io 
  PRIVATE serdes
)
target_include_directories(test_io PRIVATE ./src)