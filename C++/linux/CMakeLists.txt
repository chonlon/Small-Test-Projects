cmake_minimum_required(VERSION 3.0.2)
project(linux)
set(CMAKE_CXX_STANDARD 17)

include(./cmake/AddExe.cmake)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../header)

add_subdirectory(FileIO)
add_subdirectory(File)
add_subdirectory(signal)
add_subdirectory(thread)