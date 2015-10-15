#include "Graphics.h"
#include "OpenGL/Renderer/OpenGLRenderer.h"
#include "OpenGL/Resource/OpenGLGraphicsResourceManager.h"

namespace SamEngine
{
    void Graphics::Initialize(const GraphicsConfig &config)
    {
        s_assert(!Available());
        mConfig = config;
        switch (mConfig.Type)
        {
        case GraphicsType::OPENGL3:
            mRenderer = new OpenGLRenderer;
            mResourceManager = new OpenGLGraphicsResourceManager;
            break;
        default:
            GetLog().Error("[Graphics::Initialize] unsupport GraphicsType!\n");
            break;
        }
        mRenderer->Initialize(mConfig);
        mResourceManager->Initialize(mConfig);
    }

    void Graphics::Finalize()
    {
        s_assert(Available());
        mConfig = GraphicsConfig();
        mRenderer->Finalize();
        mRenderer = nullptr;
    }

    bool Graphics::Available()
    {
        return mConfig.Type != GraphicsType::NONE && mRenderer != nullptr && mResourceManager != nullptr;
    }

    IRenderer &Graphics::GetRenderer()
    {
        s_assert(Available());
        return *mRenderer;
    }

    IGraphicsResourceManager &Graphics::GetResourceManager()
    {
        s_assert(Available());
        return *mResourceManager;
    }

    GraphicsType Graphics::GetRendererType()
    {
        s_assert(Available());
        return mConfig.Type;
    }

    void Graphics::SetRendererType(GraphicsType type)
    {
        s_assert(Available());
        mRenderer->Finalize();
        mResourceManager->Finalize();
        delete mRenderer;
        delete mResourceManager;
        mConfig.Type = type;
        switch (mConfig.Type)
        {
        case GraphicsType::OPENGL3:
            mRenderer = new OpenGLRenderer;
            mResourceManager = new OpenGLGraphicsResourceManager;
            break;
        default:
            GetLog().Error("[Graphics::Initialize] unsupport GraphicsType!\n");
            break;
        }
        mRenderer->Initialize(mConfig);
        mResourceManager->Initialize(mConfig);
    }
}