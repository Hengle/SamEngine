include_directories(include src)

include_directories(${PROJECT_SOURCE_DIR}/Engine/External/v8pp)

if(SAM_WINDOWS)
    add_definitions("-DV8_LAUNCHER_API=__declspec(dllexport)")
else()
    add_definitions("-DV8_LAUNCHER_API=__attribute__((visibility(\"default\")))")
endif()

sam_push_source_group(include)
sam_auto_group_source(include module_public_include)
sam_pop_source_group()

sam_push_source_group(src)
sam_auto_group_source(src module_private_src)
sam_pop_source_group()

set(module_src ${module_public_include} ${module_private_src})

if(SAM_OSX)
    find_library(libv8_base v8_base)
    find_library(libv8_libbase v8_libbase)
    find_library(libv8_nosnapshot v8_nosnapshot)
    find_library(libv8_libplatform v8_libplatform)
    set(libv8 ${libv8_base} ${libv8_libbase} ${libv8_nosnapshot} ${libv8_libplatform})
endif()

sam_add_module(V8Launcher module_src Asset Core Event Graphics HTTP IO Launcher Resource Storage Window ${libv8})