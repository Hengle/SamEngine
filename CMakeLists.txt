cmake_minimum_required(VERSION 2.8)

project(SamEngine)

option(SAM_BUILD_EXAMPLES "Build examples" ON)

option(SAM_RTTI "enable c++ RTTI" OFF)
option(SAM_EXCEPTIONS "enable c++ exceptions" OFF)
option(SAM_GL_DEBUG "glad debug mode" ON)

include(cmake/sam.cmake)

add_subdirectory(Engine)

if(SAM_BUILD_EXAMPLES)
    add_subdirectory(Examples)
endif()