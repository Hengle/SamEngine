include_directories(include src)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/stb/include)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/gliml)

if(SAM_WINDOWS)
    add_definitions("-DASSET_API=__declspec(dllexport)")
endif()
add_definitions("-DSTB_IMAGE_IMPLEMENTATION")

sam_push_source_group(include)
    sam_auto_group_source(include asset_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src asset_private_src)
sam_pop_source_group()

set(asset_src ${asset_public_include} ${asset_private_src})

sam_add_module(Asset asset_src Core Graphics Event IO)