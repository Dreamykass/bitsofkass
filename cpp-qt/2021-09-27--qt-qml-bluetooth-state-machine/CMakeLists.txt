cmake_minimum_required(VERSION 3.14)

project(2021-09-27--qt-qml-bluetooth-state-machine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick Bluetooth REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick Bluetooth REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        state.h
        device.h device.cpp
        backend.h backend.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(2021-09-27--qt-qml-bluetooth-state-machine
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(2021-09-27--qt-qml-bluetooth-state-machine SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(2021-09-27--qt-qml-bluetooth-state-machine
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(2021-09-27--qt-qml-bluetooth-state-machine
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(2021-09-27--qt-qml-bluetooth-state-machine
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Bluetooth)

set_target_properties(2021-09-27--qt-qml-bluetooth-state-machine PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(2021-09-27--qt-qml-bluetooth-state-machine)
    qt_finalize_executable(2021-09-27--qt-qml-bluetooth-state-machine)
endif()
