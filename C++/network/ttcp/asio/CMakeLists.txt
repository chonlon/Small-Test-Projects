add_executable(ttcp_asio main.cpp ../common.cc)
target_include_directories(ttcp_asio PRIVATE SYSTEM ${Boost_INCLUDE_DIR})
target_link_libraries(ttcp_asio pthread Boost::program_options Boost::system)