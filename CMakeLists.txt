cmake_minimum_required(VERSION 3.6)
project(prj)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp event.cpp event.h job.cpp job.h simulator.cpp simulator.h fifo.cpp fifo.h)
add_executable(prj ${SOURCE_FILES})