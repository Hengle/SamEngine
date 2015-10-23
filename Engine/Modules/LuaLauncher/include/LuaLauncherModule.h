#pragma once

#ifndef LUA_LAUNCHER_API
#    if SAM_WINDOWS
#        define LUA_LAUNCHER_API __declspec(dllimport)
#    else
#        define LUA_LAUNCHER_API
#    endif
#endif

#include "ILuaLauncher.h"