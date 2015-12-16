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

add_subdirectory(spine)
set_target_properties(spine PROPERTIES FOLDER "External")

if (WIN32 AND NOT CYGWIN)
    add_definitions("-DLUA_BUILD_AS_DLL -DLUA_WIN")
elseif (APPLE)
    add_definitions("-DLUA_USE_MACOSX")
endif ()

include_directories(nanovg/src)
add_library(nanovg nanovg/src/nanovg.c)
set_target_properties(nanovg PROPERTIES FOLDER "External")

include_directories(lua/src)

add_library(lua SHARED lua/src/lapi.c lua/src/lcode.c lua/src/lctype.c lua/src/ldebug.c lua/src/ldo.c
    lua/src/ldump.c lua/src/lfunc.c lua/src/lgc.c lua/src/llex.c lua/src/lmem.c lua/src/lobject.c
    lua/src/lopcodes.c lua/src/lparser.c lua/src/lstate.c lua/src/lstring.c lua/src/ltable.c
    lua/src/ltm.c lua/src/lundump.c lua/src/lvm.c lua/src/lzio.c lua/src/lauxlib.c
    lua/src/lbaselib.c lua/src/lbitlib.c lua/src/lcorolib.c lua/src/ldblib.c
    lua/src/liolib.c lua/src/lmathlib.c lua/src/loslib.c lua/src/lstrlib.c
    lua/src/ltablib.c lua/src/linit.c lua/src/lutf8lib.c lua/src/loadlib.c
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

if (SAM_BUILD_LUA_MODULES)

    include_directories(luasocket/src)

    set(compat luasocket/src/compat.c luasocket/src/compat.h)
    set(auxiliar luasocket/src/auxiliar.c luasocket/src/auxiliar.h)
    set(buffer luasocket/src/buffer.c luasocket/src/buffer.h luasocket/src/io.h luasocket/src/timeout.h)
    set(except luasocket/src/except.c luasocket/src/except.h)
    set(inet luasocket/src/inet.c luasocket/src/inet.h luasocket/src/socket.h luasocket/src/io.h luasocket/src/timeout.h luasocket/src/usocket.h)
    set(io luasocket/src/io.c luasocket/src/io.h luasocket/src/timeout.h)
    set(luasocket luasocket/src/luasocket.c luasocket/src/luasocket.h luasocket/src/auxiliar.h luasocket/src/except.h luasocket/src/timeout.h luasocket/src/buffer.h luasocket/src/io.h luasocket/src/inet.h luasocket/src/socket.h luasocket/src/usocket.h luasocket/src/tcp.h luasocket/src/udp.h luasocket/src/select.h)
    set(mime luasocket/src/mime.c luasocket/src/mime.h)
    set(options luasocket/src/options.c luasocket/src/auxiliar.h luasocket/src/options.h luasocket/src/socket.h luasocket/src/io.h luasocket/src/timeout.h luasocket/src/usocket.h luasocket/src/inet.h)
    set(select luasocket/src/select.c luasocket/src/socket.h luasocket/src/io.h luasocket/src/timeout.h luasocket/src/usocket.h luasocket/src/select.h)
    set(serial luasocket/src/serial.c luasocket/src/auxiliar.h luasocket/src/socket.h luasocket/src/io.h luasocket/src/timeout.h luasocket/src/usocket.h luasocket/src/options.h luasocket/src/unix.h luasocket/src/buffer.h)
    set(tcp luasocket/src/tcp.c luasocket/src/auxiliar.h luasocket/src/socket.h luasocket/src/io.h luasocket/src/timeout.h luasocket/src/usocket.h luasocket/src/inet.h luasocket/src/options.h luasocket/src/tcp.h luasocket/src/buffer.h)
    set(timeout luasocket/src/timeout.c luasocket/src/auxiliar.h luasocket/src/timeout.h)
    set(udp luasocket/src/udp.c luasocket/src/auxiliar.h luasocket/src/socket.h luasocket/src/io.h luasocket/src/timeout.h luasocket/src/usocket.h luasocket/src/inet.h luasocket/src/options.h luasocket/src/udp.h)
    set(unix luasocket/src/unix.c luasocket/src/auxiliar.h luasocket/src/socket.h luasocket/src/io.h luasocket/src/timeout.h luasocket/src/usocket.h luasocket/src/options.h luasocket/src/unix.h luasocket/src/buffer.h)
    set(usocket luasocket/src/usocket.c luasocket/src/socket.h luasocket/src/io.h luasocket/src/timeout.h luasocket/src/usocket.h)
    set(wsocket luasocket/src/wsocket.c luasocket/src/socket.h luasocket/src/io.h luasocket/src/timeout.h luasocket/src/usocket.h)

    set(luasocket_common_src
        ${luasocket}
        ${timeout}
        ${buffer}
        ${io}
        ${auxiliar}
        ${compat}
        ${options}
        ${inet}
        ${except}
        ${select}
        ${tcp}
        ${udp}
    )

    if(WIN32)
        set(luasocket_src ${luasocket_common_src} ${wsocket})
        add_definitions("-DLUASOCKET_API=__declspec(dllexport)")
    else()
        set(luasocket_src ${luasocket_common_src} ${usocket})
        add_definitions("-DLUASOCKET_API=__attribute__((visibility(\"default\")))")
    endif()

    add_library(luasocket SHARED ${luasocket_src})

    if(WIN32)
        target_link_libraries(luasocket lua ws2_32)
    else()
        target_link_libraries(luasocket lua)
    endif()

    set_target_properties(luasocket PROPERTIES LINKER_LANGUAGE C)
    set_target_properties(luasocket PROPERTIES FOLDER "External")
    set_target_properties(luasocket PROPERTIES PREFIX "")
    set_target_properties(luasocket PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build/Contents/clib/socket")
    set_target_properties(luasocket PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Build/Contents/clib/socket")
    set_target_properties(luasocket PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Build/Contents/clib/socket")
    set_target_properties(luasocket PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/Build/Contents/clib/socket")
    set_target_properties(luasocket PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build/Contents/clib/socket")
    set_target_properties(luasocket PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Build/Contents/clib/socket")
    set_target_properties(luasocket PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Build/Contents/clib/socket")
    set_target_properties(luasocket PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/Build/Contents/clib/socket")
    set_target_properties(luasocket PROPERTIES OUTPUT_NAME "core")

    include_directories(json rapidjson/include)

    if(WIN32)
        add_definitions("-DLUAJSON_API=__declspec(dllexport)")
    else()
        add_definitions("-DLUAJSON_API=__attribute__((visibility(\"default\")))")
    endif()

    add_library(luajson SHARED json/json.cpp)
    target_link_libraries(luajson lua)

    set_target_properties(luajson PROPERTIES FOLDER "External")
    set_target_properties(luajson PROPERTIES PREFIX "")
    set_target_properties(luajson PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build/Contents/clib")
    set_target_properties(luajson PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Build/Contents/clib")
    set_target_properties(luajson PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Build/Contents/clib")
    set_target_properties(luajson PROPERTIES RUNTIME_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/Build/Contents/clib")
    set_target_properties(luajson PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build/Contents/clib")
    set_target_properties(luajson PROPERTIES LIBRARY_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/Build/Contents/clib")
    set_target_properties(luajson PROPERTIES LIBRARY_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/Build/Contents/clib")
    set_target_properties(luajson PROPERTIES LIBRARY_OUTPUT_DIRECTORY_PROFILING "${PROJECT_SOURCE_DIR}/Build/Contents/clib")
    set_target_properties(luajson PROPERTIES OUTPUT_NAME "json")

endif()