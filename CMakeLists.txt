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
set(HTTP_ONLY ON)

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
option(SAMPLE "compile samples" ON)
option(SAM_GL_DEBUG "glad debug mode" ON)

######################################################
#    initialize
######################################################

s_initialize()

######################################################
#    engine
######################################################

include_directories(engine/modules)

s_add_module(engine/modules/asset core graphics)
s_add_module(engine/modules/core)
s_add_module(engine/modules/event core)
s_add_module(engine/modules/graphics core window resource)
s_add_module(engine/modules/http core event io libcurl)
s_add_module(engine/modules/io core event)
s_add_module(engine/modules/resource core)
s_add_module(engine/modules/storage core event io)
s_add_module(engine/modules/window core)

######################################################
#    samples
######################################################

if (SAMPLE)
    s_add_sample(samples/storage_io core io storage)
    s_add_sample(samples/clear_color core event graphics resource window glad)
    s_add_sample(samples/triangle core event graphics resource window glad)
    s_add_sample(samples/quad asset core event graphics resource window glad)
    s_add_sample(samples/mario asset core event graphics http io resource window glad libcurl)
endif ()