include_directories(include src)

if(SAM_WINDOWS)
    add_definitions("-DRESOURCE_API=__declspec(dllexport)")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include resource_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src resource_private_src)
sam_pop_source_group()

set(resource_src ${resource_public_include} ${resource_private_src})

sam_add_module(Resource resource_src Core)