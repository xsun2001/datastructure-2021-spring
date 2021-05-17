project(datastructure C CXX)
cmake_minimum_required(VERSION 3.19)
add_compile_definitions(DEBUG)
set(CMAKE_CXX_STANDARD 17)

add_executable(pa2-1 pa2/1.cpp)
add_executable(pa2-1-test pa2/1test.cpp)
add_executable(pa2-2 pa2/2.cpp)
add_executable(pa2-4-1 pa2/4-1.cpp)
add_executable(pa2-4-2 pa2/4-2.cpp)

add_subdirectory(lab2)