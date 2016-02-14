include_directories(${PROJECT_SOURCE_DIR}/Engine/External/nanovg/src)

sam_push_source_group(src)
sam_auto_group_source(src example_src)
sam_pop_source_group()

sam_add_example(CanvasExample example_src Core Launcher Window Graphics)