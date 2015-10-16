include_directories(include src)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glfw/include)

if(SAM_WINDOWS)
    add_definitions("-DWINDOW_API=__declspec(dllexport)")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include module_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src module_private_src)
sam_pop_source_group()

set(module_src ${module_public_include} ${module_private_src})

sam_add_module(Window module_src Core glfw)