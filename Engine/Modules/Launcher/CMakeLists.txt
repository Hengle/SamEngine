include_directories(include src)

if(SAM_WINDOWS)
    add_definitions("-DLAUNCHER_API=__declspec(dllexport)")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include launcher_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src launcher_private_src)
sam_pop_source_group()

set(launcher_src ${launcher_public_include} ${launcher_private_src})

sam_add_module(Launcher launcher_src Core)