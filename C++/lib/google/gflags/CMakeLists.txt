cmake_minimum_required(VERSION 3.0.2)
project(gflags)

find_package(gflags CONFIG REQUIRED)


include(../../../cmake/AddSingleExeFile.cmake)

AddFilesTo(
        GFLAG
        test1.cpp
)

AddExeFromFiles("gflags_static" ${GFLAG_FILES})



