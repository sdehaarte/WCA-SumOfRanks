cmake_minimum_required(VERSION 3.22)
project(wca-sumofranks)

set(CMAKE_CXX_STANDARD 17)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Werror")

add_executable(Main
    main.cpp
    sum_of_ranks.h sum_of_ranks.cpp)