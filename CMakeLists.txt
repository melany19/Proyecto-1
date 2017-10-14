cmake_minimum_required(VERSION 3.8)
project(Proyecto-1)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp node.cpp node.h List.cpp List.h Server.cpp rmlib.h Memory.cpp Memory.h)
add_executable(Remote_Memory ${SOURCE_FILES})