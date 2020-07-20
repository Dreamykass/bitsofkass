cmake_minimum_required(VERSION 3.12.0)
project(lua_sol2 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(lua_sol2 main.cpp)

# # # # nope, because of some bug or something... sol2 is included in project dir instead
# find_package(sol2 CONFIG REQUIRED)
# target_link_libraries(lua_sol2 PRIVATE sol2::sol2)

include(FindLua)
find_package(Lua REQUIRED)
target_link_libraries(lua_sol2 PRIVATE ${LUA_LIBRARIES})
target_include_directories(lua_sol2 PRIVATE ${LUA_INCLUDE_DIR})


if(MSVC)
  target_compile_options(lua_sol2 PRIVATE /MP /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
else()
  target_compile_options(lua_sol2 PRIVATE -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)
endif()
