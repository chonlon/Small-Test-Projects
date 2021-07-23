cmake_minimum_required(VERSION 3.0.2)

add_executable(main main.cpp)
target_link_libraries(main pthread)