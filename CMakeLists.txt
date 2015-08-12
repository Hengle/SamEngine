cmake_minimum_required(VERSION 2.8)

project(SamEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(DEBUG "debug mode" ON)

if (DEBUG)
    add_definitions("-DDEBUG=1")
endif()

function(target_output_dir target)
    get_filename_component(dir "./build" ABSOLUTE)
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${dir})
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${dir})
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${dir})
    set_target_properties(${target} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILING ${dir})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${dir})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE ${dir})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG ${dir})
    set_target_properties(${target} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILING ${dir})
endfunction()

# engine

include_directories(engine)

# engine external

include_directories(engine/external)

set(external_glad_src
    engine/external/glad/glad.c
    engine/external/glad/glad.h
    engine/external/glad/khrplatform.h
)

set(external_src
    ${external_glad_src}
)

source_group(external\\glad FILES ${external_glad_src})

include_directories(engine/external/glfw/include)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(engine/external/glfw)

# engine modules

include_directories(engine/modules)

set(module_core_src
    engine/modules/core/app.h
    engine/modules/core/app.cpp
    engine/modules/core/assert.h
    engine/modules/core/class.h
    engine/modules/core/core.h
    engine/modules/core/core.cpp
    engine/modules/core/func_group.h
    engine/modules/core/func_group.cpp
    engine/modules/core/log.h
    engine/modules/core/log.cpp
    engine/modules/core/rwlock.h
    engine/modules/core/rwlock.cpp
    engine/modules/core/types.h
)

source_group(engine\\core FILES ${module_core_src})

set(module_event_src
    engine/modules/event/async_handler.h
    engine/modules/event/dispatcher.h
    engine/modules/event/event.h
    engine/modules/event/handler.h
    engine/modules/event/threading_handler.h
    engine/modules/event/threading_handler.cpp
)

source_group(engine\\event FILES ${module_event_src})

set(module_src
    ${module_core_src}
    ${module_event_src}
)

set(engine_src
    ${external_src}
    ${module_src}
)

add_library(engine ${engine_src})
target_output_dir(engine)

# sample

include_directories(sample)

# sample hello

set(sample_hello_src
    sample/Hello.cpp
)

if (WIN32)
    add_executable(Hello WIN32 ${sample_hello_src})
    target_link_libraries(Hello engine glfw opengl32)
elseif(APPLE)
    find_library(gl OpenGL)
    find_library(cv CoreVideo)
    find_library(cocoa Cocoa)
    find_library(io IOKit)
    add_executable(Hello ${sample_hello_src})
    target_link_libraries(Hello engine glfw ${gl} ${cv} ${cocoa} ${io})
else()
    add_executable(Hello ${sample_hello_src})
    target_link_libraries(Hello engine glfw opengl)
endif()

target_output_dir(Hello)