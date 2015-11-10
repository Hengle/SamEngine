include_directories(include)

aux_source_directory(src/spine spine_src)

add_library(spine ${spine_src})