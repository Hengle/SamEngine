cmake_minimum_required(VERSION 2.8)

project(SamEngine)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(DEBUG "debug mode" ON)

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

# third-party

include_directories(engine/external/glfw/include)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(engine/external/glfw)

# engine

include_directories(engine)

# engine external

include_directories(engine/external)

# engine external glad

set(external_glad_src
    engine/external/glad/glad.c
    engine/external/glad/glad.h
    engine/external/glad/khrplatform.h
)

# group engine external src

set(external_src
    ${external_glad_src}
)

source_group(external\\glad FILES ${external_glad_src})

# engine modules

include_directories(engine/modules)

# engime module core

set(module_core_src
    engine/modules/core/app.h
    engine/modules/core/app.cpp
    engine/modules/core/assert.h
    engine/modules/core/class.h
    engine/modules/core/core.h
    engine/modules/core/core.cpp
    engine/modules/core/data.h
    engine/modules/core/data.cpp
    engine/modules/core/func_group.h
    engine/modules/core/func_group.cpp
    engine/modules/core/log.h
    engine/modules/core/log.cpp
    engine/modules/core/pool.h
    engine/modules/core/rwlock.h
    engine/modules/core/rwlock.cpp
    engine/modules/core/types.h
)

source_group(engine\\core FILES ${module_core_src})

# engine module event

set(module_event_src
    engine/modules/event/async_handler.h
    engine/modules/event/dispatcher.h
    engine/modules/event/event.h
    engine/modules/event/handler.h
    engine/modules/event/threading_handler.h
    engine/modules/event/threading_handler.cpp
)

source_group(engine\\event FILES ${module_event_src})

# engine module graphics

set(module_graphics_config_src
    engine/modules/graphics/config/draw_state_config.h
    engine/modules/graphics/config/graphics_config.h
    engine/modules/graphics/config/mesh_config.h
    engine/modules/graphics/config/shader_config.h
    engine/modules/graphics/config/texture_config.h
)

source_group(engine\\graphics\\config FILES ${module_graphics_config_src})

set(module_graphics_core_src
    engine/modules/graphics/core/define.h
    engine/modules/graphics/core/draw_state_base.h
    engine/modules/graphics/core/draw_state_factory_base.h
    engine/modules/graphics/core/mesh_base.h
    engine/modules/graphics/core/mesh_factory_base.h
    engine/modules/graphics/core/renderer_base.h
    engine/modules/graphics/core/shader_base.h
    engine/modules/graphics/core/shader_factory_base.h
    engine/modules/graphics/core/texture_base.h
    engine/modules/graphics/core/texture_factory_base.h
    engine/modules/graphics/core/window_base.h
)

source_group(engine\\graphics\\core FILES ${module_graphics_core_src})

set(module_graphics_gl_src
    engine/modules/graphics/gl/gl.h
    engine/modules/graphics/gl/gl_draw_state.h
    engine/modules/graphics/gl/gl_draw_state.cpp
    engine/modules/graphics/gl/gl_draw_state_factory.h
    engine/modules/graphics/gl/gl_draw_state_factory.cpp
    engine/modules/graphics/gl/gl_mesh.h
    engine/modules/graphics/gl/gl_mesh.cpp
    engine/modules/graphics/gl/gl_mesh_factory.h
    engine/modules/graphics/gl/gl_mesh_factory.cpp
    engine/modules/graphics/gl/gl_renderer.h
    engine/modules/graphics/gl/gl_renderer.cpp
    engine/modules/graphics/gl/gl_shader.h
    engine/modules/graphics/gl/gl_shader.cpp
    engine/modules/graphics/gl/gl_shader_factory.h
    engine/modules/graphics/gl/gl_shader_factory.cpp
    engine/modules/graphics/gl/gl_texture.h
    engine/modules/graphics/gl/gl_texture.cpp
    engine/modules/graphics/gl/gl_texture_factory.h
    engine/modules/graphics/gl/gl_texture_factory.cpp
)

source_group(engine\\graphics\\gl FILES ${module_graphics_gl_src})

set(module_graphics_glfw_src
    engine/modules/graphics/glfw/glfw_window.h
    engine/modules/graphics/glfw/glfw_window.cpp
)

source_group(engine\\graphics\\glfw FILES ${module_graphics_glfw_src})

set(module_graphics_src
    engine/modules/graphics/draw_state.h
    engine/modules/graphics/draw_state_factory.h
    engine/modules/graphics/graphics.h
    engine/modules/graphics/graphics.cpp
    engine/modules/graphics/graphics_resource_manager.h
    engine/modules/graphics/graphics_resource_manager.cpp
    engine/modules/graphics/mesh.h
    engine/modules/graphics/mesh_factory.h
    engine/modules/graphics/renderer.h
    engine/modules/graphics/shader.h
    engine/modules/graphics/shader_factory.h
    engine/modules/graphics/texture.h
    engine/modules/graphics/texture_factory.h
    engine/modules/graphics/window.h
)

source_group(engine\\graphics FILES ${module_graphics_src})

set(module_graphics_src
    ${module_graphics_config_src}
    ${module_graphics_core_src}
    ${module_graphics_gl_src}
    ${module_graphics_glfw_src}
    ${module_graphics_src}
)

# engine module io

set(module_io_config_src
    engine/modules/io/config/io_config.h
)

source_group(engine\\io\\config FILES ${module_io_config_src})

set(module_io_core_src
    engine/modules/io/core/io_thread.h
    engine/modules/io/core/io_thread.cpp
)

source_group(engine\\io\\core FILES ${module_io_core_src})

set(module_io_event_src
    engine/modules/io/event/io_event_type.h
    engine/modules/io/event/io_notify_new_filesystem_event.h
    engine/modules/io/event/io_notify_replace_filesystem_event.h
    engine/modules/io/event/io_notify_delete_filesystem_event.h
    engine/modules/io/event/io_request_read_event.h
    engine/modules/io/event/io_request_write_event.h
)

source_group(engine\\io\\event FILES ${module_io_event_src})

set(module_io_filesystem_src
    engine/modules/io/filesystem/filesystem.h
    engine/modules/io/filesystem/location.h
    engine/modules/io/filesystem/location.cpp
)

source_group(engine\\io\\filesystem FILES ${module_io_filesystem_src})

set(module_io_src
    engine/modules/io/io.h
    engine/modules/io/io.cpp
)

source_group(engine\\io FILES ${module_io_src})

set(module_io_src
    ${module_io_config_src}
    ${module_io_core_src}
    ${module_io_event_src}
    ${module_io_filesystem_src}
    ${module_io_src}
)

# engine module resource

set(module_resource_src
    engine/modules/resource/resource.h
    engine/modules/resource/resource_manager.h
    engine/modules/resource/resource_manager.cpp
    engine/modules/resource/resource_pool.h
    engine/modules/resource/resource_registry.h
    engine/modules/resource/resource_registry.cpp
)

source_group(engine\\resource FILES ${module_resource_src})

# engine module storage

set(module_storage_config_src
    engine/modules/storage/config/storage_config.h
)

source_group(engine\\storage\\config FILES ${module_storage_config_src})

set(module_storage_filesystem_src
    engine/modules/storage/filesystem/storage_filesystem.h
    engine/modules/storage/filesystem/storage_filesystem.cpp
)

source_group(engine\\storage\\filesystem FILES ${module_storage_filesystem_src})

set(module_storage_src
    engine/modules/storage/storage.h
    engine/modules/storage/storage.cpp
)

source_group(engine\\storage FILES ${module_storage_src})

set(module_storage_src
    ${module_storage_config_src}
    ${module_storage_filesystem_src}
    ${module_storage_src}
)

# group engine module src

set(module_src
    ${module_core_src}
    ${module_event_src}
    ${module_graphics_src}
    ${module_io_src}
    ${module_resource_src}
    ${module_storage_src}
)

# group engine src

set(engine_src
    ${external_src}
    ${module_src}
)

# add engine lib

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
elseif (APPLE)
    find_library(gl OpenGL)
    find_library(cv CoreVideo)
    find_library(cocoa Cocoa)
    find_library(io IOKit)
    add_executable(Hello ${sample_hello_src})
    target_link_libraries(Hello engine glfw ${gl} ${cv} ${cocoa} ${io})
else ()
    add_executable(Hello ${sample_hello_src})
    target_link_libraries(Hello engine glfw opengl)
endif ()

target_output_dir(Hello)
