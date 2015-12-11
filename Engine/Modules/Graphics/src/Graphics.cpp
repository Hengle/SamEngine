#include "Graphics.h"
#include "OpenGL/Renderer/OpenGLCanvas.h"
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
            mCanvas = new OpenGLCanvas;
            mRenderer = new OpenGLRenderer;
            mResourceManager = new OpenGLGraphicsResourceManager;
            break;
        default:
            GetLog().Error("[Graphics::Initialize] unsupport GraphicsType!\n");
            break;
        }
        mRenderer->Initialize(mConfig);
        mCanvas->Initialize();
        mResourceManager->Initialize(mConfig);
    }

    void Graphics::Finalize()
    {
        s_assert(Available());
        mConfig = GraphicsConfig();
        mRenderer->Finalize();
        mCanvas->Finalize();
        mResourceManager->Finalize();
        mRenderer = nullptr;
    }

    bool Graphics::Available()
    {
        return mConfig.Type != GraphicsType::NONE && mRenderer != nullptr && mResourceManager != nullptr;
    }

    ICanvas& Graphics::GetCanvas()
    {
        return *mCanvas;
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
        mCanvas->Finalize();
        mResourceManager->Finalize();
        delete mRenderer;
        delete mResourceManager;
        mConfig.Type = type;
        switch (mConfig.Type)
        {
        case GraphicsType::OPENGL3:
            mRenderer = new OpenGLRenderer;
            mCanvas = new OpenGLCanvas;
            mResourceManager = new OpenGLGraphicsResourceManager;
            break;
        default:
            GetLog().Error("[Graphics::Initialize] unsupport GraphicsType!\n");
            break;
        }
        mRenderer->Initialize(mConfig);
        mCanvas->Initialize();
        mResourceManager->Initialize(mConfig);
    }

    GRAPHICS_API IGraphics &GetGraphics()
    {
        static Graphics instance;
        return instance;
    }
}