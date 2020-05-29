cmake_minimum_required(VERSION 3.0.0)
project(raq VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

if(MSVC)
  target_compile_options(${TARGET_NAME} PRIVATE /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
else()
  target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 )
endif()

add_executable(raq_test_1 test_1.cpp)
target_include_directories(latch_test PRIVATE F:/CodeStudio/_includes/DOCTEST)

add_executable(raq_example example.cpp)


