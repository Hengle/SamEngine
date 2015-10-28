#pragma once

#ifndef ASSET_API
#    if SAM_WINDOWS
#        define ASSET_API __declspec(dllimport)
#    else
#        define ASSET_API
#    endif
#endif

#include "Graphics/Blend.h"
#include "Graphics/Drawable.h"
#include "Graphics/Image.h"
#include "Graphics/ImageShader.h"
#include "Graphics/Mesh.h"
#include "Graphics/MeshConfig.h"
#include "Graphics/Texture.h"
#include "Graphics/TextureLoader.h"
#include "Graphics/UniformData.h"
#include "Graphics/UniformDataConfig.h"