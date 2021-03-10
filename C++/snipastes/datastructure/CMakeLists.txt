cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)

project ("data_structure")


add_executable(slist_runner "slist_runner.cpp")
target_include_directories(slist_runner PRIVATE ../../header)


add_executable(list_runner "list_runner.cpp")
target_include_directories(list_runner PRIVATE ../../header)

add_executable(vector_runner "vector_runner.cpp")
target_include_directories(vector_runner PRIVATE ../../header)