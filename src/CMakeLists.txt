cmake_minimum_required(VERSION 3.22)
project(better-sor)

set(CMAKE_CXX_STANDARD 14)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")

add_executable(better-sor
    BetterSOR.h BetterSOR.cpp)