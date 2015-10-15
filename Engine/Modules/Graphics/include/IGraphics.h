#pragma once

#include "Config/GraphicsConfig.h"
#include "Renderer/IRenderer.h"
#include "Resource/IGraphicsResourceManager.h"

namespace SamEngine
{
    class GRAPHICS_API IGraphics
    {
    public:
        virtual ~IGraphics() {}

        virtual void Initialize(const GraphicsConfig &config) = 0;

        virtual void Finalize() = 0;

        virtual bool Available() = 0;

        virtual IRenderer &GetRenderer() = 0;

        virtual IGraphicsResourceManager &GetResourceManager() = 0;

        virtual GraphicsType GetRendererType() = 0;

        virtual void SetRendererType(GraphicsType type) = 0;
    };

    extern GRAPHICS_API IGraphics &GetGraphics();
}