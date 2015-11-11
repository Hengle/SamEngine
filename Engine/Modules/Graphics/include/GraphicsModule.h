#pragma once

#ifndef GRAPHICS_API
#    if SAM_WINDOWS
#        define GRAPHICS_API __declspec(dllimport)
#    else
#        define GRAPHICS_API
#    endif
#endif

#include "Config/GraphicsConfig.h"
#include "Config/VertexBufferConfig.h"
#include "Config/IndexBufferConfig.h"
#include "Config/ShaderConfig.h"
#include "Config/ProgramConfig.h"
#include "Config/TextureConfig.h"
#include "Renderer/IRenderer.h"
#include "Resource/IGraphicsResourceManager.h"
#include "State/BlendState.h"
#include "State/ClearState.h"
#include "State/DepthStencilState.h"
#include "State/RasterizerState.h"
#include "GraphicsDefine.h"
#include "IGraphics.h"