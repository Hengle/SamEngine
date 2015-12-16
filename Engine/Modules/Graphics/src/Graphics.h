#pragma once

#include "IGraphics.h"
#include "Renderer/IRenderer.h"
#include "Resource/IGraphicsResourceManager.h"


namespace SamEngine
{
    class Graphics : public IGraphics {
    public:
        virtual void Initialize(const GraphicsConfig &config) override;

        virtual void Finalize() override;

        virtual bool Available() override;

        virtual ICanvas &GetCanvas() override;

        virtual IRenderer &GetRenderer() override;

        virtual IGraphicsResourceManager &GetResourceManager() override;

        virtual GraphicsType GetRendererType() override;

        virtual void SetRendererType(GraphicsType type) override;

    private:
        GraphicsConfig mConfig;
        ICanvas *mCanvas{ nullptr };
        IRenderer *mRenderer{ nullptr };
        IGraphicsResourceManager *mResourceManager{ nullptr };
    };
}