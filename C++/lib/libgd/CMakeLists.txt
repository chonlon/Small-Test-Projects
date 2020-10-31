cmake_minimum_required(VERSION 3.16)

project(libgd)

find_path(GD_INCLUDE_DIR gd.h)
get_filename_component(GD_INSTALL_DIR ${GD_INCLUDE_DIR} DIRECTORY)
set(GD_DEBUG_DIR ${GD_INSTALL_DIR}/debug/lib)
set(GD_RELEASE_DIR ${GD_INSTALL_DIR}/lib)
find_library(GD_LIBRARY NAMES gd PATHS ${GD_RELEASE_DIR} NO_DEFAULT_PATH)

add_executable(example example.cpp)
message(${GD_INCLUDE_DIR} " " ${GD_LIBRARY} " " ${GD_RELEASE_DIR})
target_include_directories(example SYSTEM PRIVATE ${GD_INCLUDE_DIR})
target_link_libraries(example ${GD_LIBRARY})

