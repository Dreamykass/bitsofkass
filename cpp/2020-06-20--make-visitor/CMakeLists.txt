cmake_minimum_required(VERSION 3.12.0)
project(make_visitor_proj VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(make_visitor_proj main.cpp make_visitor.hpp)


find_package(doctest CONFIG REQUIRED)
target_link_libraries(make_visitor_proj PRIVATE doctest::doctest)



if(MSVC)
  target_compile_options(make_visitor_proj PRIVATE /MP /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
else()
  target_compile_options(make_visitor_proj PRIVATE -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)
endif()
