cmake_minimum_required(VERSION 2.8)

project(ext_sort_lib)

set(SOURCE_LIB external_sort.cpp)

add_library(ext_sort_lib STATIC ${SOURCE_LIB})