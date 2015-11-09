#include "2D/ImageShader.h"

#include <GraphicsModule.h>

const char* DefaultVertexShader =
"#version 150 core\n"
"in vec2 position;\n"
"in vec2 texcoord0;\n"
"uniform mat4 uProjectionMatrix;\n"
"uniform mat4 uModelViewMatrix;\n"
"out vec2 vTexcoord;\n"
"void main() {\n"
"   vTexcoord = texcoord0;\n"
"   gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(position, 1.0, 1.0);\n"
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
    ResourceID ImageShader::mResourceID = InvalidResourceID;

    void ImageShader::Initialize()
    {
        s_assert(GetGraphics().Available());
        s_assert(mResourceID == InvalidResourceID);
        auto vsConfig = ShaderConfig::FromSource(ShaderType::VERTEX_SHADER, DefaultVertexShader);
        auto fsConfig = ShaderConfig::FromSource(ShaderType::FRAGMENT_SHADER, DefaultFragmentShader);
        auto vs = GetGraphics().GetResourceManager().Create(vsConfig, nullptr);
        auto fs = GetGraphics().GetResourceManager().Create(fsConfig, nullptr);
        auto programConfig = ProgramConfig::FromShader(vs, fs);
        mResourceID = GetGraphics().GetResourceManager().Create(programConfig, nullptr);
        GetGraphics().GetResourceManager().Destroy(vs);
        GetGraphics().GetResourceManager().Destroy(fs);
    }

    void ImageShader::Finalize()
    {
        s_assert(GetGraphics().Available());
        s_assert(mResourceID != InvalidResourceID);
        GetGraphics().GetResourceManager().Destroy(mResourceID);
        mResourceID = InvalidResourceID;
    }

    void ImageShader::Apply()
    {
        s_assert(GetGraphics().Available());
        s_assert(mResourceID != InvalidResourceID);
        GetGraphics().GetRenderer().ApplyProgram(mResourceID);
    }

    ResourceID ImageShader::GetResourceID()
    {
        if (mResourceID == InvalidResourceID)
        {
            Initialize();
        }
        return mResourceID;
    }
}