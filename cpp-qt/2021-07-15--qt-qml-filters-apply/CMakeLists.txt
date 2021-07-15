cmake_minimum_required(VERSION 3.14)

project(2021-07-15--qt-qml-filters-apply VERSION 0.1 LANGUAGES CXX)

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

set(PROJECT_SOURCES
        main.cpp
        qml.qrc
        backend.h
        backend.cpp
        image_provider.h

        distortion.h
        src/distortion/distortion.cpp
        src/distortion/distortion_common.h

        src/distortion/simple_color/brightness.h
        src/distortion/simple_color/brightness.cpp
        src/distortion/simple_color/contrast.h
        src/distortion/simple_color/contrast.cpp
        src/distortion/simple_color/grayscale.h
        src/distortion/simple_color/grayscale.cpp
        src/distortion/simple_color/nored.h
        src/distortion/simple_color/nored.cpp
        src/distortion/simple_color/nogreen.h
        src/distortion/simple_color/nogreen.cpp
        src/distortion/simple_color/noblue.h
        src/distortion/simple_color/noblue.cpp
        src/distortion/simple_color/inverted.h
        src/distortion/simple_color/inverted.cpp

        src/distortion/non_simple_color/change_range_color.h
        src/distortion/non_simple_color/change_range_color.cpp
        src/distortion/non_simple_color/change_image_color.h
        src/distortion/non_simple_color/change_image_color.cpp
        src/distortion/non_simple_color/filter2d.h
        src/distortion/non_simple_color/filter2d.cpp

        src/distortion/noise/classicnoise.h
        src/distortion/noise/classicnoise.cpp
        src/distortion/noise/opensimplex2.h
        src/distortion/noise/opensimplex2.cpp
        src/distortion/noise/opensimplex2s.h
        src/distortion/noise/opensimplex2s.cpp
        src/distortion/noise/perlin.h
        src/distortion/noise/perlin.cpp
        src/distortion/noise/cellular.h
        src/distortion/noise/cellular.cpp
        src/distortion/noise/value.h
        src/distortion/noise/value.cpp
        src/distortion/noise/value_cubic.h
        src/distortion/noise/value_cubic.cpp
        src/distortion/noise/noise_json_object.h

        src/distortion/compression/jpeg.h
        src/distortion/compression/jpeg.cpp

        src/distortion/optical/barrel.h
        src/distortion/optical/barrel.cpp
        src/distortion/optical/pincushion.h
        src/distortion/optical/pincushion.cpp
        src/distortion/optical/optical_json_object.h

        src/distortion/pixel/pixelate.h
        src/distortion/pixel/pixelate.cpp
        src/distortion/pixel/pixelatev2.h
        src/distortion/pixel/pixelatev2.cpp
        src/distortion/pixel/horizontal_drop_pixels.h
        src/distortion/pixel/horizontal_drop_pixels.cpp
        src/distortion/pixel/vertical_drop_pixels.h
        src/distortion/pixel/vertical_drop_pixels.cpp
        src/distortion/pixel/vertical_and_horizontal_drop_pixels.h
        src/distortion/pixel/vertical_and_horizontal_drop_pixels.cpp

        src/distortion/blur/gaussian_blur.h
        src/distortion/blur/gaussian_blur.cpp
        src/distortion/blur/bilateral_blur.h
        src/distortion/blur/bilateral_blur.cpp
        src/distortion/blur/median_blur.h
        src/distortion/blur/median_blur.cpp
        src/distortion/blur/classic_blur.h
        src/distortion/blur/classic_blur.cpp

        src/distortion/transformation/cropping.h
        src/distortion/transformation/cropping.cpp
        src/distortion/transformation/tilt.h
        src/distortion/transformation/tilt.cpp
        src/distortion/transformation/rotate.h
        src/distortion/transformation/rotate.cpp
        src/distortion/transformation/proximity.h
        src/distortion/transformation/proximity.cpp
        src/distortion/transformation/scale_modifier.h
        src/distortion/transformation/scale_modifier.cpp
        src/distortion/transformation/transformation_json_object.h

        src/distortion/edge_detection/sobel.h
        src/distortion/edge_detection/sobel.cpp
        src/distortion/edge_detection/laplace.h
        src/distortion/edge_detection/laplace.cpp
        src/distortion/edge_detection/canny.h
        src/distortion/edge_detection/canny.cpp

        src/distortion/flip_image/flip_vertically.h
        src/distortion/flip_image/flip_vertically.cpp
        src/distortion/flip_image/flip_horizontally.h
        src/distortion/flip_image/flip_horizontally.cpp

        src/distortion/matrix/matrix.h
        src/distortion/matrix/matrix.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(2021-07-15--qt-qml-filters-apply
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(2021-07-15--qt-qml-filters-apply SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(2021-07-15--qt-qml-filters-apply
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(2021-07-15--qt-qml-filters-apply
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(2021-07-15--qt-qml-filters-apply
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick ${OpenCV_LIBS})
include_directories(src/ ${OpenCV_INCLUDE_DIRS})

set_target_properties(2021-07-15--qt-qml-filters-apply PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(2021-07-15--qt-qml-filters-apply)
    qt_finalize_executable(2021-07-15--qt-qml-filters-apply)
endif()
