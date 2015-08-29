cmake_minimum_required(VERSION 2.8)

project(SamEngine)

######################################################
#    options
######################################################

option(DEBUG "debug mode" ON)

option(SAMPLE "compile samples" ON)

######################################################
#    definitions
######################################################

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (DEBUG)
    add_definitions("-DDEBUG=1")
endif ()

if (WIN32)
    add_definitions("-DSAM_WIN32")
    if (MINGW)
        add_definitions("-DSAM_MINGW")
    endif ()
elseif (APPLE)
    add_definitions("-DSAM_APPLE")
endif ()

######################################################
#    customize functions
######################################################

function (target_output_dir target)
    get_filename_component(dir "./build" ABSOLUTE)
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${dir})
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${dir})
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${dir})
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILING ${dir})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${dir})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${dir})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${dir})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILING ${dir})
endfunction ()

function (group_module_source dir variable)
    string(CONCAT file_match_case ${dir} "/*")
    file(GLOB file_list ${file_match_case})
    foreach (file ${file_list})
        if (IS_DIRECTORY ${file})
            group_module_source(${file} ${variable})
        endif()
    endforeach()
    string(CONCAT source_match_case_h ${dir} "/*.h")
    string(CONCAT source_match_case_c ${dir} "/*.c")
    string(CONCAT source_match_case_cpp ${dir} "/*.cpp")
    file(GLOB sources ${source_match_case_h} ${source_match_case_c} ${source_match_case_cpp})
    set(${variable} ${${variable}} ${sources} PARENT_SCOPE)
    string(CONCAT current_dir ${CMAKE_CURRENT_SOURCE_DIR} "/engine/")
    string(REPLACE ${current_dir} "" source_group ${dir})
    string(REPLACE "/" "\\\\" source_group ${source_group})
    source_group(${source_group} FILES ${sources})
endfunction ()

function (group_sample_source name dir variable)
    string(CONCAT file_match_case ${dir} "/*")
    file(GLOB file_list ${file_match_case})
    foreach (file ${file_list})
        if (IS_DIRECTORY ${file})
            group_sample_source(${name} ${file} ${variable})
        endif()
    endforeach()
    string(CONCAT source_match_case_h ${dir} "/*.h")
    string(CONCAT source_match_case_c ${dir} "/*.c")
    string(CONCAT source_match_case_cpp ${dir} "/*.cpp")
    file(GLOB sources ${source_match_case_h} ${source_match_case_c} ${source_match_case_cpp})
    set(${variable} ${${variable}} ${sources} PARENT_SCOPE)
    string(CONCAT current_dir ${CMAKE_CURRENT_SOURCE_DIR} "/sample/" ${name} "/")
    string(REPLACE ${current_dir} "" source_group ${dir})
	if (${source_group})
		string(REPLACE "/" "\\\\" source_group ${source_group})
		source_group(${source_group} FILES ${sources})
	endif ()
endfunction ()

function (add_sample dir)
    string(CONCAT file_match_case ${dir} "/*")
    file(GLOB file_list ${file_match_case})
    foreach (directory ${file_list})
        if (IS_DIRECTORY ${directory})
			string(CONCAT current_dir ${CMAKE_CURRENT_SOURCE_DIR} "/sample/")
			string(REPLACE ${current_dir} "" name ${directory})
            group_sample_source(${name} ${directory} sample_src)
            add_one_sample(${name} ${sample_src})
        endif()
    endforeach()
endfunction ()

function (add_one_sample name sources)
    if (WIN32)
        add_executable(${name} WIN32 ${sources})
        target_link_libraries(${name} engine glfw opengl32)
    elseif (APPLE)
        find_library(gl OpenGL)
        find_library(cv CoreVideo)
        find_library(cocoa Cocoa)
        find_library(io IOKit)
        add_executable(${name} ${sources})
        target_link_libraries(${name} engine glfw ${gl} ${cv} ${cocoa} ${io})
    else ()
        add_executable(${name} ${sources})
        target_link_libraries(${name} engine glfw opengl)
    endif ()
    target_output_dir(${name})
    set_target_properties(${name} PROPERTIES FOLDER "sample")
endfunction ()

######################################################
#    third-party glfw
######################################################

include_directories(engine/external/glfw/include)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

add_subdirectory(engine/external/glfw)

######################################################
#    third-party glm
######################################################

include_directories(engine/external/glm/glm)

add_subdirectory(engine/external/glm)

######################################################
#    third-party glad
######################################################

include_directories(engine/external/glad)

set(external_glad_src
    engine/external/glad/glad.h
    engine/external/glad/glad.c
    engine/external/glad/khrplatform.h
)

source_group(external\\glad FILES ${external_glad_src})

set(external_src
    ${external_glad_src}
)

######################################################
#    engine
######################################################

include_directories(engine/modules)

group_module_source(engine/modules module_src)

set(engine_src
    ${external_src}
    ${module_src}
)

add_library(engine ${engine_src})
target_output_dir(engine)

######################################################
#    samples
######################################################

if (SAMPLE)
    add_sample(sample)
endif ()