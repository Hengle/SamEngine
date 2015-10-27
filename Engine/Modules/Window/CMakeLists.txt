include_directories(include src)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glfw/include)

if(SAM_WINDOWS)
    add_definitions("-DWINDOW_API=__declspec(dllexport)")
else()
    add_definitions("-DWINDOW_API=__attribute__((visibility(\"default\")))")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include module_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src module_private_src)
sam_pop_source_group()

set(module_src ${module_public_include} ${module_private_src})

if(SAM_OSX)
    find_library(gl OpenGL)
    find_library(cv CoreVideo)
    find_library(cocoa Cocoa)
    find_library(io IOKit)
    sam_add_module(Window module_src Core glfw ${gl} ${cv} ${cocoa} ${io})
else()
    sam_add_module(Window module_src Core glfw)
endif()