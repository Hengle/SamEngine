function (s_initialize)
    if (NOT CMAKE_TOOLCHAIN_FILE)
        if (MSVC)
            include(${PROJECT_SOURCE_DIR}/cmake/platform/windows.cmake)
        elseif (APPLE)
            include(${PROJECT_SOURCE_DIR}/cmake/platform/osx.cmake)
        elseif (MINGW)
            include(${PROJECT_SOURCE_DIR}/cmake/platform/mingw.cmake)
        endif ()
    endif ()
endfunction ()

function (s_set_target_folder target)
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/build")
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/build")
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/build")
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/build")
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/build")
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/build")
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/build")
endfunction ()

function (s_group_module_source name dir variable)
    file(GLOB file_list "${dir}/*")
    foreach (file ${file_list})
        if (IS_DIRECTORY ${file})
            s_group_module_source(${name} ${file} ${variable})
        endif()
    endforeach()
    file(GLOB sources "${dir}/*.h" "${dir}/*.c" "${dir}/*.cpp")
    set(${variable} ${${variable}} ${sources} PARENT_SCOPE)
    string(REPLACE "${PROJECT_SOURCE_DIR}/engine/modules/${name}/" "" source_group ${dir})
    string(FIND ${source_group} ${PROJECT_SOURCE_DIR} index)
    if (${index} GREATER -1)
        source_group("" FILES ${sources})
    else ()
        string(REPLACE "/" "\\\\" source_group ${source_group})
        source_group(${source_group} FILES ${sources})
    endif ()
endfunction ()

function (s_add_module dir)
    get_filename_component(full_path ${dir} ABSOLUTE)
    string(REPLACE "${PROJECT_SOURCE_DIR}/engine/modules/" "" name ${full_path})
    s_group_module_source(${name} ${full_path} module_src)
    add_library(${name} ${module_src})
    foreach (dep ${ARGN})
        target_link_libraries(${name} ${dep})
    endforeach ()
    set_target_properties(${name} PROPERTIES FOLDER "modules")
endfunction ()

function (s_group_sample_source name dir variable)
    file(GLOB file_list "${dir}/*")
    foreach (file ${file_list})
        if (IS_DIRECTORY ${file})
            s_group_sample_source(${file} ${variable})
        endif()
    endforeach()
    file(GLOB sources "${dir}/*.h" "${dir}/*.c" "${dir}/*.cpp")
    set(${variable} ${${variable}} ${sources} PARENT_SCOPE)
    string(REPLACE "${PROJECT_SOURCE_DIR}/sample/${name}/" "" source_group ${dir})
    string(FIND ${source_group} ${PROJECT_SOURCE_DIR} index)
    if (${index} GREATER -1)
        source_group("" FILES ${sources})
    else ()
        string(REPLACE "/" "\\\\" source_group ${source_group})
        source_group(${source_group} FILES ${sources})
    endif ()
endfunction ()

function (s_add_sample dir)
    get_filename_component(full_path ${dir} ABSOLUTE)
    string(REPLACE "${PROJECT_SOURCE_DIR}/samples/" "" name ${full_path})
    s_group_sample_source(${name} ${full_path} sample_src)
    if (MSVC)
        add_executable(${name} WIN32 ${sample_src})
        foreach (dep ${ARGN})
            target_link_libraries(${name} ${dep})
        endforeach ()
        target_link_libraries(${name} glfw opengl32)
    elseif (APPLE)
        find_library(gl OpenGL)
        find_library(cv CoreVideo)
        find_library(cocoa Cocoa)
        find_library(io IOKit)
        add_executable(${name} ${sample_src})
        foreach (dep ${ARGN})
            target_link_libraries(${name} ${dep})
        endforeach ()
        target_link_libraries(${name} glfw ${gl} ${cv} ${cocoa} ${io})
    elseif (MINGW)
        add_executable(${name} ${sample_src})
        foreach (dep ${ARGN})
            target_link_libraries(${name} ${dep})
        endforeach ()
        target_link_libraries(${name} glfw opengl32)
    else ()
        add_executable(${name} ${sample_src})
        foreach (dep ${ARGN})
            target_link_libraries(${name} ${dep})
        endforeach ()
        target_link_libraries(${name} glfw opengl)
    endif ()
    s_set_target_folder(${name})
    set_target_properties(${name} PROPERTIES FOLDER "samples")
endfunction ()