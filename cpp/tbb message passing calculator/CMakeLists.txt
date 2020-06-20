cmake_minimum_required(VERSION 3.12.0)
project(tbb_test VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB_RECURSE sources CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE headers CONFIGURE_DEPENDS inc/*.hpp)

add_executable(tbb_test ${sources} ${headers})
target_include_directories(tbb_test PRIVATE ${CMAKE_SOURCE_DIR}/inc)



find_package(TBB CONFIG REQUIRED)
target_link_libraries(tbb_test PRIVATE TBB::tbb)

# find_package(BOOST REQUIRED COMPONENTS asio)
# find_path(BOOST_INCLUDE_DIR boost)
# include_directories(${BOOST_INCLUDE_DIR})

 find_package(cli CONFIG REQUIRED)
 target_link_libraries(tbb_test PRIVATE cli::cli)

# find_package(CLI11 CONFIG REQUIRED)
# target_link_libraries(tbb_test PRIVATE CLI11::CLI11)



if(MSVC)
  target_compile_options(tbb_test PRIVATE /MP /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
else()
  target_compile_options(tbb_test PRIVATE -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)
endif()
