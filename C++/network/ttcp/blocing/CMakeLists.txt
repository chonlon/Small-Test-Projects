add_executable(ttcp main.cpp ../common.cc)
target_link_libraries(ttcp pthread boost_program_options)
