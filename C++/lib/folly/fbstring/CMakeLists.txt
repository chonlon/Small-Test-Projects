add_executable(fbstring_basic basic.cpp)
target_link_libraries(fbstring_basic PRIVATE ${LinkLibs})
target_compile_options(fbstring_basic PRIVATE "-std=c++17")