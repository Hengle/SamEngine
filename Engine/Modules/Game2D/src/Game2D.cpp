#include "Game2D.h"

#include <WindowModule.h>
#include <GraphicsModule.h>
#include <IOModule.h>

namespace SamEngine
{
    void Game2D::Initialize(int32 width, int32 height, const char *title, const Color &backgroundColor, RootCreator creator)
    {
        s_assert(!Available());
        GetWindow().Initialize(WindowConfig::ForWindow(width, height, title));
        GetGraphics().Initialize(GraphicsConfig());
        GetIO().Initialize();
        mRoot = creator();
        mClearState.ClearColor = backgroundColor;
    }

    void Game2D::Finalize()
    {
        s_assert(Available());
        mRoot.reset();
        GetIO().Finalize();
        GetGraphics().Finalize();
        GetWindow().Finalize();
    }

    bool Game2D::Available()
    {
        return mRoot != nullptr;
    }

    bool Game2D::Draw()
    {
        s_assert(Available());
        GetGraphics().GetRenderer().ApplyTarget();
        GetGraphics().GetRenderer().ApplyClearState(mClearState);
        mRoot->Draw();
        GetGraphics().GetRenderer().Render();
        GetWindow().Present();
        return !GetWindow().ShouldClose();
    }
}