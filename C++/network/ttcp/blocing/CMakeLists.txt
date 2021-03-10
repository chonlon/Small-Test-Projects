add_executable(ttcp main.cpp ../common.cc)
target_include_directories(ttcp PRIVATE SYSTEM  ${Boost_INCLUDE_DIR})
target_link_libraries(ttcp pthread Boost::program_options)
