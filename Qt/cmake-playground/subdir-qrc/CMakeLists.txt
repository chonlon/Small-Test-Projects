cmake_minimum_required(VERSION 3.0.2)
project(cmake_subdir)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Core Gui Widgets)
#find_package(LIBGUI)

include_directories(${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(gui gui)
set_source_files_properties(${GUISRC} PROPERTIES GENERATED ON)

add_executable(cmake_subdir main.cpp ${GUISRC})
#target_link_libraries(cmake_subdir LIBGUI.dll)
