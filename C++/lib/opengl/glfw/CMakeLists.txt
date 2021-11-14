include_directories(${CMAKE_CURRENT_LIST_DIR}/../../../header)
AddExeFromFiles("${LIBS}" glfw1.cpp glversion.cpp basic_shader.cpp)