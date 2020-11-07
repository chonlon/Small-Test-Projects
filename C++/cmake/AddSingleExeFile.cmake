#add files to parent with relative prefix
macro(AddFilesToParent var_name)
    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")

    set(files_var_name  ${var_name}_FILES)

    foreach(_src ${ARGN})
        if (_relPath)
            list (APPEND ${files_var_name} "${_relPath}/${_src}")
        else()
            list (APPEND ${files_var_name} "${_src}")
        endif()
    endforeach()

    if (_relPath)
        set(${files_var_name} ${${files_var_name}} PARENT_SCOPE)
    else()
        set(${files_var_name} ${${files_var_name}})
    endif()
endmacro()

# add files current cmake
macro(AddFilesTo var_name)
    set(files_var_name  ${var_name}_FILES)

    foreach(_src ${ARGN})
        list (APPEND ${files_var_name} "${_src}")
    endforeach()

    set(${files_var_name} ${${files_var_name}})
endmacro()

function(AddExeFromFiles Libs)
    foreach(FILEPATH ${ARGN})
        get_filename_component(FILE_NAME ${FILEPATH} NAME_WE)
        add_executable(${FILE_NAME} ${FILEPATH})
        target_link_libraries(${FILE_NAME} PRIVATE ${Libs})
    endforeach()
endfunction()

function(AddExeFromFilesWithInclude Includes Libs)
    foreach(FILEPATH ${ARGN})
        get_filename_component(FILE_NAME ${FILEPATH} NAME_WE)
        add_executable(${FILE_NAME} ${FILEPATH})
        target_include_directories(${FILE_NAME} PRIVATE ${Includes})
        target_link_libraries(${FILE_NAME} PRIVATE ${Libs})
    endforeach()
endfunction()