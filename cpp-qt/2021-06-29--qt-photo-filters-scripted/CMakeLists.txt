cmake_minimum_required(VERSION 3.5)

project(2021-06-29--qt-photo-filters-scripted VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)
include(FindLua)
find_package(Lua REQUIRED)
find_package(sol2 CONFIG REQUIRED)

qt5_wrap_ui(UIS_HDRS
    src/mainwindow.ui
)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        ${UIS_HDRS}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(2021-06-29--qt-photo-filters-scripted
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(2021-06-29--qt-photo-filters-scripted SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(2021-06-29--qt-photo-filters-scripted
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(2021-06-29--qt-photo-filters-scripted PRIVATE 
    Qt${QT_VERSION_MAJOR}::Widgets 
    ${OpenCV_LIBS}
    ${LUA_LIBRARIES}
    sol2::sol2
    )
include_directories(
    ${OpenCV_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})

set_target_properties(2021-06-29--qt-photo-filters-scripted PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(2021-06-29--qt-photo-filters-scripted)
endif()
