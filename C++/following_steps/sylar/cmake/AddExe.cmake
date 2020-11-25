function(AddExeFromFilesWithLib Deps Libs Includes)
    foreach(FILEPATH ${ARGN})
        get_filename_component(FILE_NAME ${FILEPATH} NAME_WE)

        add_executable(${FILE_NAME} ${FILEPATH})
        add_dependencies(${FILE_NAME} ${Deps})
        target_link_libraries(${FILE_NAME} ${Libs})
        target_include_directories(${FILE_NAME} PRIVATE ${Includes})

        force_redefine_file_macro_for_sources(${FILE_NAME}) 
    endforeach()
endfunction()

function(AddTest Deps Libs Includes)
    foreach(FILEPATH ${ARGN})
        get_filename_component(FILE_NAME ${FILEPATH} NAME_WE)

        add_executable(${FILE_NAME} ${FILEPATH})
        add_dependencies(${FILE_NAME} ${Deps})
        target_link_libraries(${FILE_NAME} ${Libs})
        target_link_libraries(${FILE_NAME} pthread GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main)
        target_include_directories(${FILE_NAME} PRIVATE ${Includes})
        gtest_discover_tests(${FILE_NAME})

        force_redefine_file_macro_for_sources(${FILE_NAME}) 
    endforeach()
endfunction()