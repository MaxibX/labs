cmake_minimum_required(VERSION 3.21)
project(lab2)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(googletest-1.13.0/googletest)
add_executable(lab2 universe.cpp gamefield.cpp gameinterface.cpp gameconsole.cpp universe.h gamefield.h gameinterface.h gameconsole.h test.cpp)
target_link_libraries(lab2 gtest)