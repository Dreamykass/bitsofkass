
This shows a qt gui that asks to load an image, 
which is then loaded with opencv, 
which transforms the image to greyscale,
and then the image is displayed in the qt gui.


The fun part happens in `mainwindow.cpp`

1. create project in qtcreator
2. copy this to `.vscode/settings.json`
```json
{
    "cmake.configureSettings": {
        "OpenCV_DIR": "D:/Code/__cpp-libs/opencv/build",
        "Qt6_DIR": "C:/QT/6.1.1/msvc2019_64/lib/cmake/Qt6",
        "Qt6Widgets_DIR": "C:/QT/6.1.1/msvc2019_64/lib/cmake/Qt6Widgets",
        "Qt6WidgetsTools_DIR": "C:/QT/6.1.1/msvc2019_64/lib/cmake/Qt6WidgetsTools",
        "Qt6CoreTools_DIR": "C:/QT/6.1.1/msvc2019_64/lib/cmake/Qt6CoreTools",
        "Qt6GuiTools_DIR": "C:/QT/6.1.1/msvc2019_64/lib/cmake/Qt6GuiTools",
    },
}
```
3. add this to cmakelists.txt (and `${UIS_HDRS}` to `qt_add_executable()`)
```cmake
qt6_wrap_ui(UIS_HDRS
    mainwindow.ui
)
```
5. add this to cmakelists.txt where relevant
```cmake
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(opencv_hello_world ${OpenCV_LIBS})
```
6. copy the dlls
