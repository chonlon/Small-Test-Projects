project(benchmark)

find_package(benchmark REQUIRED)

add_executable(iter_subscript iter_subscript.cpp)

target_link_libraries(iter_subscript benchmark::benchmark)