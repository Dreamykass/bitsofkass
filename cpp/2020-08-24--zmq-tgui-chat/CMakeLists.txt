cmake_minimum_required(VERSION 3.12.0)
project(cppzmqchat_project VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(cppzmqchat_exe
      ${CMAKE_SOURCE_DIR}/code/_main.cpp
      ${CMAKE_SOURCE_DIR}/code/misc.hpp
      ${CMAKE_SOURCE_DIR}/code/shared_data.hpp

      ${CMAKE_SOURCE_DIR}/code/chatgui.hpp
      
      ${CMAKE_SOURCE_DIR}/code/event_internal.hpp
      ${CMAKE_SOURCE_DIR}/code/event_message.hpp

      ${CMAKE_SOURCE_DIR}/code/work_incoming.hpp
      ${CMAKE_SOURCE_DIR}/code/work_outgoing.hpp

      ${CMAKE_SOURCE_DIR}/resources/form.txt
      )

target_include_directories(cppzmqchat_exe PRIVATE ${CMAKE_SOURCE_DIR}/code)



find_package(cppzmq CONFIG REQUIRED)
target_link_libraries(cppzmqchat_exe PRIVATE cppzmq cppzmq-static)

find_package(unofficial-concurrentqueue CONFIG REQUIRED)
target_link_libraries(cppzmqchat_exe 
                      PRIVATE unofficial::concurrentqueue::concurrentqueue)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(cppzmqchat_exe PRIVATE fmt::fmt fmt::fmt-header-only)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(cppzmqchat_exe 
                      PRIVATE sfml-graphics FLAC OpenAL OpenGL Vorbis)

find_package(TGUI CONFIG REQUIRED)
target_link_libraries(cppzmqchat_exe PRIVATE tgui)



set(dkasses_compile_options_msvc
    /MP /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 
    /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 
    /w14640 /w14826 /w14905 /w14906 /w14928
    )
set(dkasses_compile_options_else
    -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast
    -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion
    -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond
    -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast
    -Wdouble-promotion -Wformat=2
    )

if(MSVC)
  target_compile_options(cppzmqchat_exe PRIVATE ${dkasses_compile_options_msvc})
else()
  target_compile_options(cppzmqchat_exe PRIVATE ${dkasses_compile_options_else})
endif()
