#pragma once

#include "GraphicsModule.h"

#include <LuaIntf.h>

using namespace LuaIntf;

namespace SamEngine
{
    inline static void OpenGraphicsModule(LuaState state)
    {
        LuaBinding(state).beginModule("SamEngine")
            .addProperty("Graphics", &GetGraphics)
            .beginClass<IGraphics>("IGraphics")
                .addProperty("RendererType", &IGraphics::GetRendererType, &IGraphics::SetRendererType)
                .addProperty("Renderer", &IGraphics::GetRenderer)
                .addProperty("ResourceManager", &IGraphics::GetResourceManager)
            .endClass()
            .beginClass<IRenderer>("IRenderer")
            .endClass()
            .beginClass<IGraphicsResourceManager>("IGraphicsResourceManager")
            .endClass()
        .endModule();
    }
}