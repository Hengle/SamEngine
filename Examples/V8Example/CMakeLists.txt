include_directories(${PROJECT_SOURCE_DIR}/Engine/External/v8pp)

sam_push_source_group(src)
    sam_auto_group_source(src example_src)
sam_pop_source_group()

sam_add_window_example(V8Example example_src V8Launcher)