include_directories(include src)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/luasocket/src)

if(SAM_WINDOWS)
    add_definitions("-DLUA_LAUNCHER_API=__declspec(dllexport)")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include module_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src module_private_src)
sam_pop_source_group()

set(module_src ${module_public_include} ${module_private_src})

sam_add_module(LuaLauncher module_src Asset Core Event Graphics HTTP IO Launcher Resource Storage Window lua luasocket)