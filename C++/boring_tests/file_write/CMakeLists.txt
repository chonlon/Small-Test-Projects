cmake_minimum_required(VERSION 3.0.1)

project(file_write)

find_package(fmt CONFIG REQUIRED)

add_executable(file_write_test "file_write_test.cpp")
target_include_directories(file_write_test PRIVATE "../../header")
target_link_libraries(file_write_test PRIVATE fmt::fmt fmt::fmt-header-only)