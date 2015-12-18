include_directories(include src)

include_directories(${PROJECT_SOURCE_DIR}/Engine/External/glm/glm)

if(SAM_WINDOWS)
    add_definitions("-DWINDOW_API=__declspec(dllexport)")
else()
    add_definitions("-DWINDOW_API=__attribute__((visibility(\"default\")))")
endif()

sam_push_source_group(include)
    sam_auto_group_source(include module_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src module_private_src)
sam_pop_source_group()

set(module_src ${module_public_include} ${module_private_src})

find_library(libGLFW3 glfw3)

if(SAM_OSX)
    find_library(libCoreVideo CoreVideo)
    find_library(libCocoa Cocoa)
    find_library(libIOKit IOKit)
    find_library(libCarbon Carbon)
    set(libGLFW3 ${libGLFW3} ${libOpenGL} ${libCoreVideo} ${libCocoa} ${libIOKit} ${libCarbon})
endif()

sam_add_module(Window module_src Core ${libGLFW3})