# 可选 STATIC或者SHARED, 默认的是STATIC.
add_library(MathFunctions mysqrt.cxx)



# 添加包含路径, 相当于编译期 -I
# 主要是几种:
# [BEFORE] 加到所有包含目录之前, 意味着: 这个目录的优先级最高;
# [SYSTEM] 和 g++ -isystem类似, 添加包含路径, 告诉编译器这是系统包含目录, 同时包含路径内的文件的warning不影响项目的;
# <INTERFACE|PUBLIC|PRIVATE>:
#   INTERFACE, 自己不使用, 链接此库的会自动包含(INTERFACE_INCLUDE_DIRECTORIES);
#   PUBLIC, 外部可见, 和INTERFACE的区别就是自己会用(INCLUDE_DIRECTORIES & INTERFACE_INCLUDE_DIRECTORIES);
#   PRIVATE, 外部不可见(INCLUDE_DIRECTORIES);
#   SYSTEM与PUBLIC或者INTERFACE一起使用会导致填充的路径变成(INTERFACE_SYSTEM_INCLUDE_DIRECTORIES)而不是上面的.(就是告诉外部这也是system的, 详细可以在这里看: https://cmake.org/cmake/help/latest/prop_tgt/INTERFACE_SYSTEM_INCLUDE_DIRECTORIES.html#prop_tgt:INTERFACE_SYSTEM_INCLUDE_DIRECTORIES)
# see https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories
target_include_directories(MathFunctions
          PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
          )

message(STATUS "MathFunc dir: " ${CMAKE_CURRENT_LIST_DIR})
message(STATUS "MathFunc src dir: " ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS "MathFunc bin: " ${CMAKE_CURRENT_BINARY_DIR})
