cmake_minimum_required(VERSION 2.8)

project(SamEngine)

include(cmake/sam.cmake)

######################################################
#    options
######################################################

option(SAM_EXCEPTIONS "enable c++ exceptions" OFF)
option(SAMPLE "compile samples" ON)

######################################################
#    initialize
######################################################

s_initialize()

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

######################################################
#    third-party glad
######################################################

include_directories(engine/external/glad)

add_subdirectory(engine/external/glad)

######################################################
#    engine
######################################################

include_directories(engine/modules)

s_add_module(engine/modules/core)
s_add_module(engine/modules/event core)
s_add_module(engine/modules/graphics core)
s_add_module(engine/modules/io core event)
s_add_module(engine/modules/resource core)
s_add_module(engine/modules/storage core event io)

######################################################
#    samples
######################################################

if (SAMPLE)
	s_add_sample(samples/storage_io core io storage)
    s_add_sample(samples/clear_color core event graphics resource glad)
endif ()