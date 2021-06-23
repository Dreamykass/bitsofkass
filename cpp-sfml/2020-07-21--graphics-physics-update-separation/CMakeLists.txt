cmake_minimum_required(VERSION 3.12.0)
project(separation_proj VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



set(sep_sources ${CMAKE_SOURCE_DIR}/src/main.cpp ${CMAKE_SOURCE_DIR}/src/graphics.cpp ${CMAKE_SOURCE_DIR}/src/physics.cpp)
set(sep_headers ${CMAKE_SOURCE_DIR}/include/common.hpp ${CMAKE_SOURCE_DIR}/include/graphics.hpp ${CMAKE_SOURCE_DIR}/include/physics.hpp)

add_executable(separation_exec ${sep_sources} ${sep_headers})
target_include_directories(separation_exec PRIVATE ${CMAKE_SOURCE_DIR}/include)



find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(separation_exec PRIVATE sfml-system sfml-window sfml-graphics OpenGL)



set(dkasses_compile_options_msvc /MP /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
set(dkasses_compile_options_else -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)

if(MSVC)
  target_compile_options(separation_exec PRIVATE ${dkasses_compile_options_msvc})
else()
  target_compile_options(separation_exec PRIVATE ${dkasses_compile_options_else})
endif()
