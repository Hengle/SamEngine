include_directories(include src)
include_directories(${CMAKE_BINARY_DIR}/Engine/External/curl/include/curl)
include_directories(${PROJECT_SOURCE_DIR}/Engine/External/curl/include/curl)

if(SAM_WINDOWS)
    add_definitions("-DHTTP_API=__declspec(dllexport)")
endif()

add_definitions("-DCURL_STATICLIB")

sam_push_source_group(include)
    sam_auto_group_source(include http_public_include)
sam_pop_source_group()

sam_push_source_group(src)
    sam_auto_group_source(src http_private_src)
sam_pop_source_group()

set(http_src ${http_public_include} ${http_private_src})

sam_add_module(HTTP http_src Core Event IO libcurl)