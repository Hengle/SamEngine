include_directories(include src)

if(SAM_WINDOWS)
    add_definitions("-DIO_API=__declspec(dllexport)")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include io_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src io_private_src)
sam_pop_source_group()

set(io_src ${io_public_include} ${io_private_src})

sam_add_module(IO io_src Core Event)