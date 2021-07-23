cmake_minimum_required(VERSION 3.14)

project(2021-07-20--qt-rest LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core REQUIRED)
find_package(Qt5Network REQUIRED)

add_executable(2021-07-20--qt-rest
  main.cpp
  config_load.cpp
  config.json
  config.h
)
target_link_libraries(2021-07-20--qt-rest Qt${QT_VERSION_MAJOR}::Core Qt5::Network)

#file(COPY config.json DESTINATION ${CMAKE_BINARY_DIR})
configure_file(config.json ${CMAKE_BINARY_DIR} COPYONLY)
