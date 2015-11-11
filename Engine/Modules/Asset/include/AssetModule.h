#pragma once

#ifndef ASSET_API
#    if SAM_WINDOWS
#        define ASSET_API __declspec(dllimport)
#    else
#        define ASSET_API
#    endif
#endif

#include "2D/Blend.h"
#include "2D/Image.h"
#include "2D/ImageShader.h"
#include "Graphics/Drawable.h"
#include "Graphics/IndexBuilder.h"
#include "Graphics/Mesh.h"
#include "Graphics/Texture.h"
#include "Graphics/TextureLoader.h"
#include "Graphics/VertexBuilder.h"