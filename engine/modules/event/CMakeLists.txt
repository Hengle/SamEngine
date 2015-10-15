include_directories(include src)

if(SAM_WINDOWS)
    add_definitions("-DEVENT_API=__declspec(dllexport)")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include event_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src event_private_src)
sam_pop_source_group()

set(event_src ${event_public_include} ${event_private_src})

sam_add_module(Event event_src Core)