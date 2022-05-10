#cmake_minimum_required(VERSION 3.0.2)
#project(cmake_subdir)


set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(${CMAKE_CURRENT_LIST_DIR})
find_package(Qt5 COMPONENTS Core Gui Widgets)
set(
	GUISRC
	${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.ui
	${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.h
	${CMAKE_CURRENT_SOURCE_DIR}/MainWindow.cpp
)

set (
	GUIQRC
	${CMAKE_CURRENT_SOURCE_DIR}/icon.qrc
)

set(
	#GUISRC ${GUIQRC} PARENT_SCOPE
	GUISRC ${GUIQRC} ${GUISRC}
)


add_library(LIBGUI STATIC ${GUISRC})
target_link_libraries(LIBGUI Qt5::Widgets Qt5::Gui Qt5::Core)
