# Helper function to get all subdirectories
function(get_subdirectories result current_dir)
    set(dir_list "")
    file(GLOB children ${current_dir}/*)
    
    foreach(child ${children})
        if(IS_DIRECTORY ${child})
            list(APPEND dir_list ${child})
    
            get_subdirectories(subdir_list ${child})
    
            list(APPEND dir_list ${subdir_list})
        endif()
    endforeach()
    
    set(${result} ${dir_list} PARENT_SCOPE)
endfunction()
