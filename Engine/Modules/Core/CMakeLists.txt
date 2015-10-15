include_directories(include src)

if(SAM_WINDOWS)
    add_definitions("-DCORE_API=__declspec(dllexport)")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include core_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src core_private_src)
sam_pop_source_group()

set(core_src ${core_public_include} ${core_private_src})

sam_add_module(Core core_src)