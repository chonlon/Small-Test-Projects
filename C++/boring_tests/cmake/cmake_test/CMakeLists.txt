cmake_minimum_required(VERSION 3.15)
project(Test VERSION 1.0)

configure_file(Config.h.in ${CMAKE_CURRENT_LIST_DIR}/Config.h)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED true)

option(USE_MYMATH "Use math" ON)

if(USE_MYMATH)
  add_subdirectory(MathFunctions)
  list(APPEND EXTRA_LIBS MathFunctions)
endif()

add_executable(Test test.cxx)

# cmake 生成器..
set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(Test INTERFACE
  "$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
  "$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)

# 链接库; 相当于编译期中的-l...
# 主要三种属性:
# PUBLIC:成为链接接口的一部分, 自己会使用这些链接库 一般用于链接lib
# PRIVATE:仅自己使用: 一般用来链接executable ###常用
# INTERFACE:成为链接接口的一部分, 但自己不使用 一般用于lib
# 默认没加的相当于PUBLIC ###常用
target_link_libraries(Test PUBLIC ${EXTRA_LIBS})
target_include_directories(Test
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
target_sources(Test
    PRIVATE
        test.hpp
        foo.cpp
)


message(STATUS "proj bin: " ${PROJECT_BINARY_DIR})
message(STATUS "main dir: " ${CMAKE_CURRENT_LIST_DIR})
message(STATUS "main bin: " ${CMAKE_CURRENT_BINARY_DIR})
message(STATUS "main src dir: " ${CMAKE_CURRENT_SOURCE_DIR})

message(STATUS "cmake module path: " ${CMAKE_MODULE_PATH})