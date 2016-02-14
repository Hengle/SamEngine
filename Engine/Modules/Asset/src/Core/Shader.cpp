#include "Core/Shader.h"

namespace SamEngine
{
    Shader::Shader(const std::string &vertex, const std::string &fragment, const std::vector<std::pair<std::string, UniformAttributeFormat>> &uniforms)
    {
        auto vsConfig = ShaderConfig::FromSource(ShaderType::VERTEX_SHADER, vertex);
        auto fsConfig = ShaderConfig::FromSource(ShaderType::FRAGMENT_SHADER, fragment);
        auto vs = GetGraphics().GetResourceManager().Create(vsConfig, nullptr);
        auto fs = GetGraphics().GetResourceManager().Create(fsConfig, nullptr);
        auto programConfig = ProgramConfig::FromShader(vs, fs);
        for (auto pair : uniforms)
        {
            programConfig.Uniform.Add(pair.first, pair.second);
        }
        mResourceID = GetGraphics().GetResourceManager().Create(programConfig, nullptr);
        GetGraphics().GetResourceManager().Destroy(vs);
        GetGraphics().GetResourceManager().Destroy(fs);
    }

    Shader::~Shader()
    {
        GetGraphics().GetResourceManager().Destroy(mResourceID);
    }

    void Shader::Apply()
    {
        GetGraphics().GetRenderer().ApplyProgram(mResourceID);
    }
}