project(range)
set(CMAKE_CXX_STANDARD 17)
find_package(range-v3 CONFIG REQUIRED)
add_executable(itoa itoa.cpp)
target_link_libraries(itoa PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)

add_executable(enumerate enumerate.cpp)
target_link_libraries(enumerate  PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)

add_executable(conact conact.cpp)
target_link_libraries(conact PRIVATE range-v3 range-v3-meta range-v3::meta range-v3-concepts)