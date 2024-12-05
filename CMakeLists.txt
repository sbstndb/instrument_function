cmake_minimum_required(VERSION 3.10)

project(Add_instrumented)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finstrument-functions")

add_executable(add src/main.cpp src/instrument.c)

