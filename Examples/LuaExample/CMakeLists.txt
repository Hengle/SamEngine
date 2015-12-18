include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glm/glm)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/lua-intf/LuaIntf)

sam_push_source_group(src)
    sam_auto_group_source(src example_src)
sam_pop_source_group()

sam_add_window_example(LuaExample example_src LuaLauncher)