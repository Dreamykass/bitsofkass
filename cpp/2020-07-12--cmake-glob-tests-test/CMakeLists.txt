cmake_minimum_required(VERSION 3.12.0)
project(my_project VERSION 0.1.0)

include(CTest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



file(GLOB_RECURSE my_test_files_list CONFIGURE_DEPENDS tests/*.cpp)

foreach(element_in_list ${my_test_files_list})
  file(RELATIVE_PATH element_in_list_relative ${CMAKE_SOURCE_DIR}/tests ${element_in_list})
  add_executable(${element_in_list_relative} ${element_in_list})
  add_test(NAME ${element_in_list_relative} COMMAND ${element_in_list_relative})
  # message("added executable: " ${element_in_list_relative})
endforeach()



set(my_compile_options_msvc /MP /permissive /W4 /w14640 /w14242 /w14254 /w14263 /w14265 /w14287 /we4289 /w14296 /w14311 /w14545 /w14546 /w14547 /w14549 /w14555 /w14619 /w14640 /w14826 /w14905 /w14906 /w14928)
set(my_compile_options_else -Wall -Wextra -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2)

foreach(element_in_list ${my_test_files_list})
  file(RELATIVE_PATH element_in_list_relative ${CMAKE_SOURCE_DIR}/tests ${element_in_list})

  if(MSVC)
    target_compile_options(${element_in_list_relative} PRIVATE ${soptargsi_compile_options_msvc})
  else()
    target_compile_options(${element_in_list_relative} PRIVATE ${soptargsi_compile_options_else})
  endif()
endforeach()


# add_custom_command(
#   TARGET ${UNIT_TEST}
#   COMMENT "Run tests"
#   POST_BUILD
#   WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
#   COMMAND ${CMAKE_CTEST_COMMAND} -C $<CONFIGURATION> -R "^${UNIT_TEST}$" --output-on-failures
# )