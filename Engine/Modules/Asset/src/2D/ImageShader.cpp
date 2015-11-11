#include "2D/ImageShader.h"

#include <GraphicsModule.h>

#include <gtc/matrix_transform.inl>

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
        programConfig.UniformLayout
            .Add("uProjectionMatrix", UniformAttributeFormat::MATRIX4)
            .Add("uModelViewMatrix", UniformAttributeFormat::MATRIX4)
            .Add("uTexture", UniformAttributeFormat::TEXTURE);
        mResourceID = GetGraphics().GetResourceManager().Create(programConfig, nullptr);
        GetGraphics().GetResourceManager().Destroy(vs);
        GetGraphics().GetResourceManager().Destroy(fs);
        SetUniformData(0, glm::ortho(0.0f, static_cast<float32>(GetWindow().GetConfig().Width), 0.0f, static_cast<float32>(GetWindow().GetConfig().Height)));
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
}