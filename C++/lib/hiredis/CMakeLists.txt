cmake_minimum_required(VERSION 3.16)
project(hiredis)
find_package(hiredis CONFIG REQUIRED)
set(CMAKE_VERBOSE_MAKEFILE true)

add_executable(basic basic.cpp)
target_include_directories(basic SYSTEM PRIVATE  "/home/lon/2_lib/vcpkg/installed/x64-linux/include/")
target_link_libraries(basic PRIVATE hiredis::hiredis)
target_compile_options(basic PRIVATE "-fpermissive;")