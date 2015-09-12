cmake_minimum_required(VERSION 2.8)

project(SamEngine)

######################################################
#    third-party glfw
######################################################

include_directories(engine/external/glfw/include)

set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

add_subdirectory(engine/external/glfw)
set_target_properties(glfw PROPERTIES FOLDER "external")

######################################################
#    third-party glm
######################################################

include_directories(engine/external/glm/glm)

######################################################
#    third-party glad
######################################################

if (SAM_GL_DEBUG)
    include_directories(engine/external/glad_debug/include)
    add_subdirectory(engine/external/glad_debug)
else ()
    include_directories(engine/external/glad/include)
    add_subdirectory(engine/external/glad)
endif ()

set_target_properties(glad PROPERTIES FOLDER "external")

######################################################
#    third-party stb
######################################################

add_definitions("-DSTB_IMAGE_IMPLEMENTATION")
include_directories(engine/external/stb)

######################################################
#    third-party glm
######################################################

include_directories(engine/external/gliml)

######################################################
#    third-party curl
######################################################

set(BUILD_CURL_EXE OFF)
set(BUILD_CURL_TESTS OFF)
set(CURL_STATICLIB ON)
set(HTTP_ONLY ON)

add_definitions("-DCURL_STATICLIB")
include_directories(${CMAKE_CURRENT_BINARY_DIR}/engine/external/curl/include/curl engine/external/curl/include)
add_subdirectory(engine/external/curl)
set_target_properties(libcurl PROPERTIES FOLDER "external")

######################################################
#    cmake
######################################################

include(cmake/sam.cmake)

######################################################
#    options
######################################################

option(SAM_RTTI "enable c++ RTTI" OFF)
option(SAM_EXCEPTIONS "enable c++ exceptions" OFF)
option(SAM_GL_DEBUG "glad debug mode" ON)

option(SAM_BUILD_SAMPLE "compile samples" ON)

######################################################
#    initialize
######################################################

s_initialize()

######################################################
#    engine
######################################################

if (MSVC)
    set(SAM_OPENGL_LIB "opengl32")
elseif (APPLE)
    find_library(gl OpenGL)
    find_library(cv CoreVideo)
    find_library(cocoa Cocoa)
    find_library(io IOKit)
    set(SAM_OPENGL_LIB ${gl} ${cv} ${cocoa} ${io})
elseif (MINGW)
    set(SAM_OPENGL_LIB "opengl32")
else ()
    set(SAM_OPENGL_LIB "GL")
endif ()

include_directories(engine/modules)

s_add_module(engine/modules/asset core graphics)
s_add_module(engine/modules/core)
s_add_module(engine/modules/event core)
s_add_module(engine/modules/graphics core window resource glad ${SAM_OPENGL_LIB})
s_add_module(engine/modules/http core event io libcurl)
s_add_module(engine/modules/io core event)
s_add_module(engine/modules/resource core)
s_add_module(engine/modules/storage core event io)
s_add_module(engine/modules/window core glfw)

######################################################
#    samples
######################################################

if (SAM_BUILD_SAMPLE)
    s_add_sample(engine/samples/storage_io)
    s_add_sample(engine/samples/clear_color)
    s_add_sample(engine/samples/triangle)
    s_add_sample(engine/samples/quad)
    s_add_sample(engine/samples/mario)
endif ()