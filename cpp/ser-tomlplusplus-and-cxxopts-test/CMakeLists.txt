cmake_minimum_required(VERSION 3.12.0)
project(tomlplusplus_test_p VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(tomlplusplus_test_p main.cpp scope_exit.hpp)



find_path(RANG_INCLUDE_DIR NAMES rang.hpp PATH_SUFFIXES rang)
include_directories(${RANG_INCLUDE_DIR})

include_directories(F:/CodeStudio/_libs/TOMLPLUSPLUS/include)

find_package(cxxopts CONFIG REQUIRED)
target_link_libraries(tomlplusplus_test_p PRIVATE cxxopts::cxxopts)



if(MSVC)
  target_compile_options(tomlplusplus_test_p
 PRIVATE /MP /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
else()
  target_compile_options(tomlplusplus_test_p
 PRIVATE -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)
endif()
