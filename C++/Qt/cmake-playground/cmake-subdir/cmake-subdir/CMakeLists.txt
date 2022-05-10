cmake_minimum_required(VERSION 3.9)
project(cmake_subdir)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)


add_executable(cmake_subdir main.cpp)

add_subdirectory(gui)

target_include_directories(cmake_subdir PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(cmake_subdir Qt5::Widgets Qt5::Gui Qt5::Core)
