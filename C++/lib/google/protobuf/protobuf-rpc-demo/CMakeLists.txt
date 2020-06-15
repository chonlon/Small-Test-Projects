PROJECT(protobuf-rpc-demp)
cmake_minimum_required(VERSION 3.2)

find_package(protobuf CONFIG REQUIRED)

include_directories(
    ./src)



set(LIBMYRPC_SRC ./src/rpc_meta.pb.cc)
add_library(myrpc ${LIBMYRPC_SRC})
add_executable(server ./src/echo.pb.cc ./src/test_myrpc.cpp)
target_link_libraries(server protobuf::libprotobuf libboost_signals.a libboost_system.a myrpc)
add_executable(client ./src/echo.pb.cc ./src/test_myrpc_client.cpp)
target_link_libraries(client protobuf::libprotobuf  libboost_signals.a libboost_system.a myrpc)
