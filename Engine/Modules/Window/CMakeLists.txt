include_directories(include src)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glfw/include)

if(SAM_WINDOWS)
    add_definitions("-DWINDOW_API=__declspec(dllexport)")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include window_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src window_private_src)
sam_pop_source_group()

set(window_src ${window_public_include} ${window_private_src})

sam_add_module(Window window_src Core glfw)