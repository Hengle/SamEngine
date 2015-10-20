#include "Game2D.h"

#include <WindowModule.h>
#include <GraphicsModule.h>
#include <IOModule.h>

#include <gtc/matrix_transform.hpp>

const char* DefaultVertexShader =
"#version 150 core\n"
"in vec2 position;\n"
"in vec2 texcoord0;\n"
"uniform mat4 uProjectionMatrix;\n"
"uniform mat4 uMVPMatrix;\n"
"out vec2 vTexcoord;\n"
"void main() {\n"
"   vTexcoord = texcoord0;\n"
"   gl_Position = uProjectionMatrix * uMVPMatrix * vec4(position, 1.0, 1.0);\n"
"}";

const char* DefaultFragmentShader =
"#version 150 core\n"
"in vec2 vTexcoord;\n"
"uniform sampler2D uTexture;\n"
"out vec4 outColor;\n"
"void main() {\n"
"   outColor = texture(uTexture, vTexcoord);\n"
"}";

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
        mDefaultShader = mShaderManager.AddShader(DefaultVertexShader, DefaultFragmentShader);
        mShaderManager.UseShader(mDefaultShader);
        mProjectionMatrix = glm::ortho(0.0f, static_cast<float32>(width), 0.0f, static_cast<float32>(height));
    }

    void Game2D::Finalize()
    {
        s_assert(Available());
        mRoot.reset();
        mShaderManager.Destroy();
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