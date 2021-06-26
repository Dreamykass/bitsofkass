cmake_minimum_required(VERSION 3.16.0)
project(qt_hello_world_project VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_PREFIX_PATH "C:/QT/6.1.1/msvc2019_64/lib/cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

qt6_wrap_ui(UIS_HDRS
    mainwindow.ui
)



add_executable(qt_hello_world
      main.cpp
      mainwindow.cpp
      mainwindow.ui
      mainwindow.h
      ${UIS_HDRS}
      )



target_link_libraries(qt_hello_world PRIVATE Qt6::Widgets)



# set(dkasses_compile_options_msvc
#     /MP /fpermissive- /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 
#     /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 
#     /w14640 /w14826 /w14905 /w14906 /w14928
#     )
# set(dkasses_compile_options_else
#     -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast
#     -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion
#     -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond
#     -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast
#     -Wdouble-promotion -Wformat=2
#     )

if(MSVC)
  target_compile_options(qt_hello_world PRIVATE ${dkasses_compile_options_msvc})
else()
  target_compile_options(qt_hello_world PRIVATE ${dkasses_compile_options_else})
endif()
