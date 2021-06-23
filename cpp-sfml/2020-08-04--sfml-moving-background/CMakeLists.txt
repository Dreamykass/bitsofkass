cmake_minimum_required(VERSION 3.0.0)
project(tests VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

add_executable(test main.cpp)

find_package(
  SFML
  COMPONENTS system window graphics CONFIG
  REQUIRED)
target_link_libraries(test PRIVATE sfml-graphics FLAC OpenAL OpenGL Vorbis)
