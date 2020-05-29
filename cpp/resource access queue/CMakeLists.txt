cmake_minimum_required(VERSION 3.0.0)
project(raq VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

get_filename_component(DIR_ONE_ABOVE ../ ABSOLUTE)


add_executable(raq_test_1 test_1.cpp aqueue.hpp)
target_include_directories(raq_test_1 PRIVATE F:/CodeStudio/_includes/DOCTEST)
target_include_directories(raq_test_1 PRIVATE ${DIR_ONE_ABOVE}/latch)

add_executable(raq_example example.cpp aqueue.hpp)
target_include_directories(raq_example PRIVATE ${DIR_ONE_ABOVE}/latch)

if(MSVC)
  target_compile_options(raq_test_1 PRIVATE /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
  target_compile_options(raq_example PRIVATE /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
else()
  target_compile_options(raq_test_1 PRIVATE -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 )
  target_compile_options(raq_example PRIVATE -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 )
endif()
