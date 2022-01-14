cmake_minimum_required(VERSION 3.0.2)

find_package(Boost REQUIRED COMPONENTS system thread)

add_executable(main main.cpp)
target_link_libraries(main pthread Boost::system Boost::thread)