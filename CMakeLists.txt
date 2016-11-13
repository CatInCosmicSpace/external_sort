cmake_minimum_required(VERSION 2.8)

project(external_sort)

set (CMAKE_CXX_FLAGS "-std=c++1y -static-libgcc -static-libstdc++")

set(SOURCE_EXE main.cpp)

include_directories(lib)

add_executable(external_sort ${SOURCE_EXE})

add_subdirectory(lib)

target_link_libraries(external_sort ext_sort_lib)