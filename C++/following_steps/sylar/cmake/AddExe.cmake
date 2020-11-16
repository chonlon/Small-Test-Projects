function(AddExeFromFilesWithLib Deps Libs Includes)
    foreach(FILEPATH ${ARGN})
        get_filename_component(FILE_NAME ${FILEPATH} NAME_WE)

        add_executable(${FILE_NAME} ${FILEPATH})
        add_dependencies(${FILE_NAME} ${Deps})
        target_link_libraries(${FILE_NAME} ${Libs})
        target_include_directories(${FILE_NAME} PRIVATE ${Includes})

    endforeach()
endfunction()