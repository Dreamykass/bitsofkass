cmake_minimum_required(VERSION 3.14)

project(2021-07-22--qt-zipping LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(libzip CONFIG REQUIRED)

file(GLOB_RECURSE GLOBBED_SOURCES CONFIGURE_DEPENDS *.cpp *.h *.hpp)

add_executable(2021-07-22--qt-zipping
  main.cpp
  ${GLOBBED_SOURCES}
)
target_link_libraries(2021-07-22--qt-zipping Qt${QT_VERSION_MAJOR}::Core libzip::zip)
include_directories()
