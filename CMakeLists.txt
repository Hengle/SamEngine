cmake_minimum_required(VERSION 3.1)

project(SamEngine)

option(SAM_USE_LUA "Use Lua script" OFF)

option(SAM_BUILD_EXAMPLES "Build examples" ON)

option(SAM_RTTI "enable c++ RTTI" OFF)
option(SAM_GL_DEBUG "glad debug mode" ON)

include(cmake/sam.cmake)

sam_initialize()

add_subdirectory(Engine)

if(SAM_BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()