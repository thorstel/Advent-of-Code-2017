cmake_minimum_required(VERSION 3.8.0)

project(AoC2017 CXX)

if(CMAKE_COMPILER_IS_GNUCXX
        OR(CMAKE_C_COMPILER_ID MATCHES "Clang")
        OR(CMAKE_CXX_COMPILER_ID MATCHES "Clang"))
    set(CXX_FLAGS -O3 -march=native -Wall -Wextra -Wpedantic -pedantic -pedantic-errors)
endif()

find_package(Threads)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(inc)

add_executable(aoc17
    inc/aoc_utility.hpp
    inc/default_includes.hpp
    inc/solution.hpp
    src/aoc_utility.cpp
    src/day01.cpp
    src/day02.cpp
    src/day03.cpp
    src/day04.cpp
    src/day05.cpp
    src/day06.cpp
    src/day07.cpp
    src/day08.cpp
    src/day09.cpp
    src/day10.cpp
    src/day11.cpp
    src/day12.cpp
    src/day13.cpp
    src/day14.cpp
    src/day15.cpp
    src/day16.cpp
    src/day17.cpp
    src/day18.cpp
    src/day19.cpp
    src/day20.cpp
    src/day21.cpp
    src/day22.cpp
    src/day23.cpp
    src/day24.cpp
    src/day25.cpp
    src/runner.cpp
    src/solution.cpp)

target_compile_options(aoc17 PUBLIC ${CXX_FLAGS})

install(TARGETS aoc17 RUNTIME DESTINATION ${PROJECT_SOURCE_DIR})
