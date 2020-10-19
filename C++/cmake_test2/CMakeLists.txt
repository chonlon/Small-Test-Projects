cmake_minimum_required(VERSION 3.16)
project(test2)

add_executable(main)
target_sources(main PRIVATE main.cpp)

add_subdirectory(sub)
