cmake_minimum_required (VERSION 3.10)

include(${CMAKE_CURRENT_LIST_DIR}/../cmake/conan_libs.cmake)

add_executable (first_assigment "main.cpp" )

target_link_libraries(first_assigment CONAN_PKG::sfml)
