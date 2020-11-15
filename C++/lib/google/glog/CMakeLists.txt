cmake_minimum_required(VERSION 3.0.2)
project(glog)

find_package(glog  REQUIRED)
find_package(gflags  REQUIRED)

add_executable(glog1 glog1.cpp)
target_link_libraries(glog1 glog::glog gflags_static)
#target_link_libraries(glog1 glog::glog)