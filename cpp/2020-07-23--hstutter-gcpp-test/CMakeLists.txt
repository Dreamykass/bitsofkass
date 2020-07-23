cmake_minimum_required(VERSION 3.12.0)
project(gcpp_my_proj VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# help-paths-set.cmake is supposed to contain: 
#      set(my_gcpp_path "path/to/gcpp")
#      set(my_gsl_path "path/to/gcpp")
include(${CMAKE_SOURCE_DIR}/help-paths-set.cmake)
if((NOT DEFINED my_gcpp_path) OR (NOT DEFINED my_gsl_path))
  message(FATAL_ERROR "----either my_gcpp_path or my_gsl_path is not defined :(")
endif()
if((NOT EXISTS "${my_gcpp_path}/deferred_heap.h") OR (NOT EXISTS "${my_gsl_path}/gsl/gsl"))
  message("----my_gcpp_path does not contain deferred_heap.h, and its value is: " ${my_gcpp_path})
  message("----or my_gsl_path does not contain gsl/gsl, and its values is: " ${my_gsl_path})
  message(FATAL_ERROR "----(look up)")
endif()



add_executable(gcpp_my_exec ${CMAKE_SOURCE_DIR}/main.cpp)
target_include_directories(gcpp_my_exec PRIVATE ${my_gcpp_path})
target_include_directories(gcpp_my_exec PRIVATE ${my_gsl_path})



set(dkasses_compile_options_msvc /MP /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
set(dkasses_compile_options_else -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)

if(MSVC)
  target_compile_options(gcpp_my_exec PRIVATE ${dkasses_compile_options_msvc})
else()
  target_compile_options(gcpp_my_exec PRIVATE ${dkasses_compile_options_else})
endif()
