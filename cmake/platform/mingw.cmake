message("Target Platform: MinGW")

set(SAM_PLATFORM MinGW)
set(SAM_PLATFORM_NAME "mingw")

set(SAM_WINDOWS 1)
set(SAM_MINGW 1)

set(CMAKE_CONFIGURATION_TYPES Debug Release)

if (SAM_RTTI)
    message("C++ RTTI is enabled")
    set(SAM_MINGW_RTTI_FLAGS "")
else()
    message("C++ RTTI is disabled")
    set(SAM_MINGW_RTTI_FLAGS "-fno-rtti")
endif()

set(CMAKE_CXX_FLAGS "${SAM_MINGW_RTTI_FLAGS} -std=c++11 -Wall -Wextra -Wno-multichar -Wno-unused-parameter -Wno-unused-function -Wno-sign-compare -DSAM_MINGW=1")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ftree-vectorize -msse3 -ffast-math -DNDEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -D_DEBUG_ -D_DEBUG -DSAM_DEBUG=1 -ggdb")

set(CMAKE_C_FLAGS "-Wall -Wextra -Wno-unused-parameter -Wno-unused-function -Wno-sign-compare -DSAM_MINGW=1")
set(CMAKE_C_FLAGS_RELEASE "-O3 -ftree-vectorize -msse3 -ffast-math -DNDEBUG")
set(CMAKE_C_FLAGS_DEBUG "-O0 -D_DEBUG_ -D_DEBUG -DSAM_DEBUG=1 -ggdb")

set(CMAKE_EXE_LINKER_FLAGS "")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "")

set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Config Type" FORCE)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}" CACHE STRING "Generic C++ Compiler Flags" FORCE)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "C++ Debug Compiler Flags" FORCE)
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}" CACHE STRING "C++ Release Compiler Flags" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "Generic C Compiler Flags" FORCE)
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "C Debug Compiler Flags" FORCE)
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}" CACHE STRING "C Release Compiler Flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}" CACHE STRING "Generic Linker Flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "Debug Linker Flags" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE}" CACHE STRING "Release Linker Flags" FORCE)


if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Compile Type" FORCE)
endif()

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release)