include_directories(include src)

if(SAM_USE_LUA)
    include_directories(${PROJECT_SOURCE_DIR}/Engine/External/lua-intf/LuaIntf)
    add_definitions("-DSAM_USE_LUA=1")
endif()

if(SAM_WINDOWS)
    add_definitions("-DLAUNCHER_API=__declspec(dllexport)")
else()
    add_definitions("-DLAUNCHER_API=__attribute__((visibility(\"default\")))")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include module_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src module_private_src)
sam_pop_source_group()

set(module_src ${module_public_include} ${module_private_src})

sam_add_module(Launcher module_src Core)