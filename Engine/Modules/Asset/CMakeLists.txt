include_directories(include src)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/stb/include)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/gliml)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/spine/include)

if(SAM_WINDOWS)
    add_definitions("-DASSET_API=__declspec(dllexport)")
else()
    add_definitions("-DASSET_API=__attribute__((visibility(\"default\")))")
endif()
add_definitions("-DSTB_IMAGE_IMPLEMENTATION")

sam_push_source_group(include)
    sam_auto_group_source(include module_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src module_private_src)
sam_pop_source_group()

set(module_src ${module_public_include} ${module_private_src})

sam_add_module(Asset module_src Core Graphics Event IO Storage spine)