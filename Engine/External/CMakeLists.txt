if (SAM_GL_DEBUG)
    add_subdirectory(glad_debug)
else ()
    add_subdirectory(glad)
endif ()
set_target_properties(glad PROPERTIES FOLDER "External")

add_subdirectory(spine)
set_target_properties(spine PROPERTIES FOLDER "External")

include_directories(nanovg/src)
add_library(nanovg nanovg/src/nanovg.c)
set_target_properties(nanovg PROPERTIES FOLDER "External")

include_directories(mongoose)
add_library(mongoose mongoose/mongoose.c)
set_target_properties(mongoose PROPERTIES FOLDER "External")

if(SAM_ANDROID)
    include_directories(${ANDROID_NDK}/sources/android/native_app_glue)
    add_library(android_native_app_glue ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
endif()