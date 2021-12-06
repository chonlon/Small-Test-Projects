cmake_minimum_required(VERSION 3.10)

project(OpenGLBasic)
# for linux it is glfw3
find_package(glfw3 REQUIRED)

INCLUDE_DIRECTORIES(include)

LINK_LIBRARIES(dl glfw)

add_executable(1_version 1_version.cpp src/glad.c)
add_executable(2_triangle 2_triangle.cpp src/glad.c)
