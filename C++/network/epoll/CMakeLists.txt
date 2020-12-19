cmake_minimum_required(VERSION 3.0.2)

set(CMAKE_CXX_STANDARD 11)

add_executable(multi_client client.cpp)
add_executable(epoll_server server.cpp)

target_link_libraries(multi_client pthread)