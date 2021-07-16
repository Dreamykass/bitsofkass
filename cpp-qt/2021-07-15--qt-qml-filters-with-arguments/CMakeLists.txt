cmake_minimum_required(VERSION 3.14)

project(2021-07-15--qt-qml-filters-with-arguments VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
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

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)
find_package(OpenCV REQUIRED)

file(GLOB_RECURSE GLOBBED_SOURCES CONFIGURE_DEPENDS *.cpp *.h)

set(PROJECT_SOURCES
        src/qml.qrc
        src/main.qml
        ${GLOBBED_SOURCES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(2021-07-15--qt-qml-filters-with-arguments
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(2021-07-15--qt-qml-filters-with-arguments SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(2021-07-15--qt-qml-filters-with-arguments
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(2021-07-15--qt-qml-filters-with-arguments
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(2021-07-15--qt-qml-filters-with-arguments
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick ${OpenCV_LIBS})
include_directories(src/ ${OpenCV_INCLUDE_DIRS})

set_target_properties(2021-07-15--qt-qml-filters-with-arguments PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(2021-07-15--qt-qml-filters-with-arguments)
    qt_finalize_executable(2021-07-15--qt-qml-filters-with-arguments)
endif()
