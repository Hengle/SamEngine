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