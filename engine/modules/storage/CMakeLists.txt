include_directories(include src)

if(SAM_WINDOWS)
    add_definitions("-DSTORAGE_API=__declspec(dllexport)")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include storage_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src storage_private_src)
sam_pop_source_group()

set(storage_src ${storage_public_include} ${storage_private_src})

sam_add_module(Storage storage_src Core Event IO)