cmake_minimum_required(VERSION 3.14)

project(2021-07-23--qt-zipping LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)

add_executable(2021-07-23--qt-zipping
  main.cpp
  zip.h
  zip.cpp
  miniz.h
)
target_link_libraries(2021-07-23--qt-zipping Qt${QT_VERSION_MAJOR}::Core)
