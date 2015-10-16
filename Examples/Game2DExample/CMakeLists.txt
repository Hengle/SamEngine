include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glm/glm)

sam_push_source_group(src)
    sam_auto_group_source(src example_src)
sam_pop_source_group()

sam_add_window_example(Game2DExample example_src Game2D)