cmake_minimum_required(VERSION 3.0.0)
project(latch VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(latch_test test.cpp)
target_include_directories(latch_test PRIVATE F:/CodeStudio/_includes/DOCTEST)

add_executable(latch_example example.cpp)


