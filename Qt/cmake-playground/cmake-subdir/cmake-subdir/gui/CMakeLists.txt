cmake_minimum_required(VERSION 3.0.2)
project(cmake_subdir)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_LIST_DIR})
find_package(Qt5 COMPONENTS Core Gui Widgets)
set(
	GUISRC
	widget.ui
	widget.h
	widget.cpp
)

add_library(LIBGUI STATIC ${GUISRC})
target_link_libraries(LIBGUI Qt5::Widgets Qt5::Gui Qt5::Core)
