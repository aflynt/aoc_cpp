cmake_minimum_required(VERSION 3.5)

project(aoc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(aoc main.cpp
    day01.cpp
    day02.cpp
    day03.cpp
    day04.cpp
    day05.cpp
    day06.cpp
    day07.cpp
    day08.cpp
    day09.cpp
    day10.cpp
    game.cpp
    gridpos.cpp
    card.cpp
    aoc_lib.cpp
    )

target_include_directories(aoc PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
