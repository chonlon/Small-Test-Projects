cmake_minimum_required(VERSION 3.10)

project(fmt)
set(CMAKE_CXX_STANDARD 17)

find_package(RapidJSON)
find_package(fmt REQUIRED)

include(../../cmake/AddSingleExeFile.cmake)

AddFilesTo(
    Fmt
    basic.cpp
    num.cpp
    range.cpp
    format_to.cpp
)
set(
    LinkLibs
    fmt::fmt
)

if(RapidJSON_FOUND)

endif()

AddExeFromFiles("${LinkLibs}" ${Fmt_FILES})
