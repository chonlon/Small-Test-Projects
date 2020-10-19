cmake_minimum_required(VERSION 3.16)
project(simple_contact)

find_package(Boost 1.67 COMPONENTS system program_options REQUIRED)
find_package(asss 1.1)
find_path(BOOST_ASIO_INCLUDE_DIRS "boost/asio.hpp")


add_executable(client client.cpp)
target_link_libraries(client PRIVATE ${Boost_LIBRARIES} pthread)
#message(DEBUG ${Boost_LIBRARIES})
target_include_directories(client PUBLIC ${Boost_INCLUDE_DIR})
#target_link_directories(client PRIVATE "/home/lon/2_lib/vcpkg/installed/x64-linux/lib/")
#target_link_libraries(client boost_system boost_program_options pthread)

add_executable(server server.cpp)