#pragma once

#ifndef LAUNCHER_API
#    if SAM_WINDOWS
#        define LAUNCHER_API __declspec(dllimport)
#    else
#        define LAUNCHER_API
#    endif
#endif

#include "IApplication.h"
#include "ILauncher.h"
#include "ILuaLauncher.h"