cmake_minimum_required(VERSION 3.8)
project(ex2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES ikea.cpp ikea.h Product.cpp Product.h)
add_executable(ex2 ${SOURCE_FILES})