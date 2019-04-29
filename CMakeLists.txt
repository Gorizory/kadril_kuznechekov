cmake_minimum_required(VERSION 3.13)
project(kadril_kuznechekov)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-O3")

add_executable(kadril_kuznechekov src/main.cpp src/header.h)