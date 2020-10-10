project(simple_contact)

add_executable(client client.cpp)
target_link_libraries(client boost_system boost_program_options pthread)

add_executable(server server.cpp)