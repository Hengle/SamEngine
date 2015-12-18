#pragma once

#ifndef V8_LAUNCHER_API
#    if SAM_WINDOWS
#        define V8_LAUNCHER_API __declspec(dllimport)
#    else
#        define V8_LAUNCHER_API
#    endif
#endif

#include "IV8Launcher.h"