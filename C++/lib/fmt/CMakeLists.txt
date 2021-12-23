cmake_minimum_required(VERSION 3.10)

project(fmt)

find_package(RapidJSON)
find_package(fmt REQUIRED)

include(../../cmake/AddSingleExeFile.cmake)

AddFilesTo(
    Fmt
    basic.cpp
    num.cpp
)
set(
    LinkLibs
    fmt::fmt
)

if(RapidJSON_FOUND)

endif()

AddExeFromFiles("${LinkLibs}" ${Fmt_FILES})
