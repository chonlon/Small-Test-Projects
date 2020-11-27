cmake_minimum_required(VERSION 3.10)

project(sylar)

option(EnableTests "BUILD TESTS" OFF)
option(EnableRunner "BUILD RUNNER" OFF)

find_package(Boost REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)
    

include(./cmake/AddExe.cmake)
include(./cmake/utils.cmake)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_CXX_STANDARD 11)

set(CXX_FLAGS
    # -DVALGRIND
    -DCHECK_PTHREAD_RETURN_VALUE
    -D_FILE_OFFSET_BITS=64
    -Wall
    -Wextra
    -Werror
    -Wconversion
    -Wno-unused-parameter
    -Wold-style-cast
    -Woverloaded-virtual
    -Wpointer-arith
    -Wshadow
    -Wwrite-strings
    -march=native
    # -MMD
    -rdynamic
    #ignore
    -Wno-builtin-macro-redefined
    )
if(CMAKE_BUILD_BITS EQUAL 32)
  list(APPEND CXX_FLAGS "-m32")
endif()
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  list(APPEND CXX_FLAGS "-Wno-null-dereference")
  list(APPEND CXX_FLAGS "-Wno-sign-conversion")
  list(APPEND CXX_FLAGS "-Wno-unused-local-typedef")
  list(APPEND CXX_FLAGS "-Wthread-safety")
  list(REMOVE_ITEM CXX_FLAGS "-rdynamic")
endif()
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

message(STATUS "CXX_FLAGS = " ${CMAKE_CXX_FLAGS} " " ${CMAKE_CXX_FLAGS_${BUILD_TYPE}})

add_library(sylar SHARED)
force_redefine_file_macro_for_sources(sylar) #重定义__FILE__
target_sources(sylar PRIVATE
        "sylar/log.cc"
        "sylar/util.cc"
        "sylar/util.h"
        "sylar/config.h"
        "sylar/config.cc"
        "sylar/thread.cc"
        "sylar/macro.h"
        "sylar/fiber.h"
        "sylar/fiber.cc"
        "sylar/scheduler.h"
        "sylar/scheduler.cc")
target_include_directories(sylar SYSTEM PUBLIC  ${Boost_INCLUDE_DIRS})

target_link_libraries(sylar PUBLIC yaml-cpp pthread)

if(EnableRunner)
set(
    Runners
    runner/runner_log.cc
    runner/runner_config.cc
    runner/runner_thread.cc
    runner/runner_utils.cc
    runner/runner_fiber.cc
)

AddExeFromFilesWithLib("sylar" "sylar" "sylar/" ${Runners})

configure_file("./bin/conf/log.yml" "${EXECUTABLE_OUTPUT_PATH}/log.yml" COPYONLY)
message(STATUS "runner was enabled")
endif()

if(EnableTests)
    enable_testing()
    add_subdirectory(test)
    message(STATUS "test was enabled")
endif()


