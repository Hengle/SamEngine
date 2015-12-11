#pragma once

#include "IGraphics.h"
#include "Renderer/IRenderer.h"
#include "Resource/IGraphicsResourceManager.h"


namespace SamEngine
{
    class Graphics : public IGraphics {
    public:
        void Initialize(const GraphicsConfig &config) override;

        void Finalize() override;

        bool Available() override;

        ICanvas &GetCanvas() override;

        IRenderer &GetRenderer() override;

        IGraphicsResourceManager &GetResourceManager() override;

        GraphicsType GetRendererType() override;

        void SetRendererType(GraphicsType type) override;

    private:
        GraphicsConfig mConfig;
        ICanvas *mCanvas{ nullptr };
        IRenderer *mRenderer{ nullptr };
        IGraphicsResourceManager *mResourceManager{ nullptr };
    };
}