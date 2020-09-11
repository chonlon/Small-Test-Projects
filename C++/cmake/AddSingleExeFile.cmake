macro(AddSingleExeFile var_name)
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