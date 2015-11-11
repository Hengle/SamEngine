#include "2D/DefaultShader.h"

#include <gtc/matrix_transform.inl>

namespace SamEngine
{
    const char *DefaultVertexShader[static_cast<uint8>(DefaultShaderType::COUNT)] =
    {
        "#version 150 core\n"
        "in vec2 aPosition;\n"
        "in vec2 aTexcoord0;\n"
        "uniform mat4 uProjectionMatrix;\n"
        "uniform mat4 uModelViewMatrix;\n"
        "out vec2 vTexcoord;\n"
        "void main() {\n"
        "   vTexcoord = aTexcoord0;\n"
        "   gl_Position = uProjectionMatrix * uModelViewMatrix * vec4(aPosition, 1.0, 1.0);\n"
        "}"
    };

    const char *DefaultFragmentShader[static_cast<uint8>(DefaultShaderType::COUNT)] =
    {
        "#version 150 core\n"
        "in vec2 vTexcoord;\n"
        "uniform sampler2D uTexture;\n"
        "out vec4 outColor;\n"
        "void main() {\n"
        "   outColor = texture(uTexture, vTexcoord);\n"
        "}"
    };

    const std::vector<std::pair<std::string, UniformAttributeFormat>> DefaultShaderUniforms[static_cast<uint8>(DefaultShaderType::COUNT)] =
    {
        {{ "uProjectionMatrix", UniformAttributeFormat::MATRIX4 }, { "uModelViewMatrix", UniformAttributeFormat::MATRIX4 }, { "uTexture", UniformAttributeFormat::TEXTURE } }
    };

    ShaderPtr DefaultShader::mShaderCache[] = { nullptr };

    void DefaultShader::Initialize()
    {
        for (auto i = 0; i < static_cast<int8_t>(DefaultShaderType::COUNT); ++i)
        {
            s_assert(mShaderCache[i] == nullptr);
            mShaderCache[i] = Shader::Create(DefaultVertexShader[i], DefaultFragmentShader[i], DefaultShaderUniforms[i]);
            mShaderCache[i]->SetUniformData(static_cast<uint8>(DefaultShaderUniformIndex::PROJECTION_MATRIX), glm::ortho(0.0f, static_cast<float32>(GetWindow().GetConfig().Width), 0.0f, static_cast<float32>(GetWindow().GetConfig().Height)));
        }
    }

    void DefaultShader::Finalize()
    {
        for (auto i = 0; i < static_cast<int8_t>(DefaultShaderType::COUNT); ++i)
        {
            mShaderCache[i].reset();
        }
    }

    ShaderPtr DefaultShader::GetShader(DefaultShaderType type)
    {
        s_assert(mShaderCache[0] != nullptr);
        s_assert(type != DefaultShaderType::COUNT);
        return mShaderCache[static_cast<int8_t>(type)];
    }
}