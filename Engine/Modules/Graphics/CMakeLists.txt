include_directories(include src)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glm/glm)

if(SAM_GL_DEBUG)
    include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glad_debug/include)
else()
    include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glad/include)
endif()

if(SAM_WINDOWS)
    add_definitions("-DGRAPHICS_API=__declspec(dllexport)")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include graphics_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src graphics_private_src)
sam_pop_source_group()

set(graphics_src ${graphics_public_include} ${graphics_private_src})

if(SAM_WINDOWS)
    set(SAM_OPENGL_LIB "opengl32")
elseif(SAM_OSX)
    find_library(gl OpenGL)
    find_library(cv CoreVideo)
    find_library(cocoa Cocoa)
    find_library(io IOKit)
    set(SAM_OPENGL_LIB ${gl} ${cv} ${cocoa} ${io})
elseif(SAM_LINUX)
    set(SAM_OPENGL_LIB "GL")
endif()

sam_add_module(Graphics graphics_src Core Window Resource glad ${SAM_OPENGL_LIB})