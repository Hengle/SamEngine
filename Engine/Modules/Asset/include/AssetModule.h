#pragma once

#ifndef ASSET_API
#    if SAM_WINDOWS
#        define ASSET_API __declspec(dllimport)
#    else
#        define ASSET_API
#    endif
#endif

#include "2D/Blend.h"
#include "2D/DefaultShader.h"
#include "2D/Image.h"
#include "2D/ImageBatcher.h"
#include "2D/Spine.h"
#include "3D/Mesh.h"
#include "Core/Drawable.h"
#include "Core/Shader.h"
#include "Core/Texture.h"
#include "Util/IndexBuilder.h"
#include "Util/VertexBuilder.h"
