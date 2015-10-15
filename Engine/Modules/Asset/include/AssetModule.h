#pragma once

#ifndef ASSET_API
#    if SAM_WINDOWS
#        define ASSET_API __declspec(dllimport)
#    else
#        define ASSET_API
#    endif
#endif

#include "Graphics/Mesh.h"
#include "Graphics/MeshConfig.h"
#include "Graphics/TextureLoader.h"