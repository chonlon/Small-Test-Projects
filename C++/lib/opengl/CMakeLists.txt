cmake_minimum_required(VERSION 3.18)

project(opengl)

include(../../cmake/AddSingleExeFile.cmake)
find_package(OpenGL REQUIRED)
# may be other version?
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${CMAKE_CURRENT_LIST_DIR}/../../header)

set(LIBS glfw OpenGL::GL ${GLEW_LIBRARIES})

add_subdirectory(glfw)