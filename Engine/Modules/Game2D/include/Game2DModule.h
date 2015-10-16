#pragma once

#ifndef CORE_API
#    if SAM_WINDOWS
#        define GAME2D_API __declspec(dllimport)
#    else
#        define GAME2D_API
#    endif
#endif

#include "Core/DefaultShader.h"
#include "Display/Image.h"
#include "Display/Sprite.h"
#include "IGame2D.h"