cmake_minimum_required(VERSION 3.12.0)
project(asio_daytime_project VERSION 0.1.0)
project(asio_daytime_project VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(client main_client.cpp pretty_printer.hpp pretty_printer.cpp)
add_executable(server main_server.cpp pretty_printer.hpp pretty_printer.cpp)



find_path(RANG_INCLUDE_DIR NAMES rang.hpp PATH_SUFFIXES rang)
target_include_directories(client PRIVATE ${RANG_INCLUDE_DIR})
target_include_directories(server PRIVATE ${RANG_INCLUDE_DIR})

find_package(asio CONFIG REQUIRED)
target_link_libraries(client PRIVATE asio asio::asio)
target_link_libraries(server PRIVATE asio asio::asio)

# set(_WIN32_WINNT _WIN32_WINNT_VISTA)



if(MSVC)
  target_compile_options(client PRIVATE /MP /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
  target_compile_options(server PRIVATE /MP /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
else()
  target_compile_options(client PRIVATE -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)
  target_compile_options(server PRIVATE -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)
endif()
