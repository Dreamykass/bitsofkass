cmake_minimum_required(VERSION 3.12.0)
project(executable_producer_turtle VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(executable_producer_turtle.exe_turtle exe.cpp)



add_subdirectory(${CMAKE_SOURCE_DIR}/internal_lib)
target_link_libraries(executable_producer_turtle.exe_turtle PRIVATE internal_library_kitty.ilib_kitty)
target_include_directories(executable_producer_turtle.exe_turtle PRIVATE "${CMAKE_SOURCE_DIR}/internal_lib")


find_library(elib_doggy_path REQUIRED NAMES external_lib_doggy.elib_doggy PATHS "${CMAKE_SOURCE_DIR}/../external_lib/build/Debug")
target_link_libraries(executable_producer_turtle.exe_turtle PRIVATE ${elib_doggy_path})
target_include_directories(executable_producer_turtle.exe_turtle PRIVATE "${CMAKE_SOURCE_DIR}/../external_lib")


find_library(elib_parrot_path REQUIRED NAMES external_lib_parrot.elib_parrot PATHS "${CMAKE_SOURCE_DIR}/../external_lib_shared/build/Debug")
target_link_libraries(executable_producer_turtle.exe_turtle PRIVATE ${elib_parrot_path})
target_include_directories(executable_producer_turtle.exe_turtle PRIVATE "${CMAKE_SOURCE_DIR}/../external_lib_shared")


#find_package(elib_doggy_path REQUIRED NAMES external_lib_doggy.elib_doggy HINTS "${CMAKE_SOURCE_DIR}/../external_lib")
#target_link_libraries(executable_producer_turtle.exe_turtle PRIVATE "${elib_doggy_path}")
#target_include_directories(executable_producer_turtle.exe_turtle PRIVATE "${elib_doggy_path}")



set(my_compile_options_msvc /MP /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
set(my_compile_options_else -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)

if(MSVC)
  target_compile_options(executable_producer_turtle.exe_turtle PRIVATE ${my_compile_options_msvc})
else()
  target_compile_options(executable_producer_turtle.exe_turtle PRIVATE ${my_compile_options_else})
endif()
