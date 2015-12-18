#pragma once

#include "GraphicsModule.h"

#include <LuaIntf.h>

using namespace LuaIntf;

namespace SamEngine
{
    inline static void OpenGraphicsLuaModule(LuaState state)
    {
        LuaBinding(state).beginModule("SamEngine")
            .addProperty("Graphics", &GetGraphics)
            .beginClass<IGraphics>("IGraphics")
                .addProperty("RendererType", &IGraphics::GetRendererType, &IGraphics::SetRendererType)
                .addProperty("Renderer", &IGraphics::GetRenderer)
                .addProperty("ResourceManager", &IGraphics::GetResourceManager)
                .addMetaFunction("Clear", [](uint32 color)
                {
                    static ClearState clearState;
                    clearState.ClearColor.r = static_cast<uint8>((color >> 24) & 0xFF);
                    clearState.ClearColor.g = static_cast<uint8>((color >> 16) & 0xFF);
                    clearState.ClearColor.b = static_cast<uint8>((color >> 8) & 0xFF);
                    clearState.ClearColor.a = static_cast<uint8>(color & 0xFF);
                    GetGraphics().GetRenderer().ApplyClearState(clearState);
                }, LUA_ARGS(_def<uint32, 0xffffffff>))
            .endClass()
            .beginClass<IRenderer>("IRenderer")
            .endClass()
            .beginClass<IGraphicsResourceManager>("IGraphicsResourceManager")
            .endClass()
        .endModule();
    }
}