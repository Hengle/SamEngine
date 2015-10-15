#pragma once

#ifndef WINDOW_API
#    if SAM_WINDOWS
#        define WINDOW_API __declspec(dllimport)
#    else
#        define WINDOW_API
#    endif
#endif

#include "IWindow.h"
#include "WindowConfig.h"
#include "WindowDefine.h"