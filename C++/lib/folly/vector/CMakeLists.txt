add_executable(fbvector ${CMAKE_CURRENT_LIST_DIR}/fbvector.cpp)
target_link_libraries(fbvector ${FbvectorLinkLibs})

add_executable(fbvector_custom_alloctor ${CMAKE_CURRENT_LIST_DIR}/fbvector_custom_alloctor.cpp)
target_link_libraries(fbvector_custom_alloctor ${FbvectorLinkLibs})