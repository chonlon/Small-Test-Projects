
find_package(glad)
find_package(glfw3)
add_executable(main main.cpp)

target_link_libraries(main PRIVATE glad::glad glfw::glfw)
