cmake_minimum_required(VERSION 3.10)

project(OpenGLBasic)

INCLUDE_DIRECTORIES(include)

LINK_LIBRARIES(dl)

add_executable(1_version 1_version.cpp src/glad.c)
