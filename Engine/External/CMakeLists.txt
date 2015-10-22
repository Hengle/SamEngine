set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)

add_subdirectory(glfw)
set_target_properties(glfw PROPERTIES FOLDER "External")

if (SAM_GL_DEBUG)
    add_subdirectory(glad_debug)
else ()
    add_subdirectory(glad)
endif ()
set_target_properties(glad PROPERTIES FOLDER "External")

set(BUILD_CURL_EXE OFF)
set(BUILD_CURL_TESTS OFF)
set(CURL_STATICLIB ON)
set(HTTP_ONLY ON)

add_subdirectory(curl)
set_target_properties(libcurl PROPERTIES FOLDER "External")

if (WIN32 AND NOT CYGWIN)
    add_definitions("-DLUA_BUILD_AS_DLL -DLUA_WIN")
else ()
endif ()

include_directories(lua/src)

add_library(lua SHARED 
    lua/src/lapi.c
    lua/src/lcode.c
    lua/src/lctype.c
    lua/src/ldebug.c
    lua/src/ldo.c
    lua/src/ldump.c
    lua/src/lfunc.c
    lua/src/lgc.c
    lua/src/llex.c
    lua/src/lmem.c
    lua/src/lobject.c
    lua/src/lopcodes.c
    lua/src/lparser.c
    lua/src/lstate.c
    lua/src/lstring.c
    lua/src/ltable.c
    lua/src/ltm.c
    lua/src/lundump.c
    lua/src/lvm.c
    lua/src/lzio.c
    lua/src/lauxlib.c
    lua/src/lbaselib.c
    lua/src/lbitlib.c
    lua/src/lcorolib.c
    lua/src/ldblib.c
    lua/src/liolib.c
    lua/src/lmathlib.c
    lua/src/loslib.c
    lua/src/lstrlib.c
    lua/src/ltablib.c
    lua/src/linit.c
    lua/src/lutf8lib.c
    lua/src/loadlib.c
)
set_target_properties(lua PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(lua PROPERTIES FOLDER "External")
set_target_properties(lua PROPERTIES PREFIX "")
set_target_properties(lua PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build")
set_target_properties(lua PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Build")
set_target_properties(lua PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Build")
set_target_properties(lua PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/Build")
set_target_properties(lua PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build")
set_target_properties(lua PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Build")
set_target_properties(lua PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Build")
set_target_properties(lua PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/Build")