#include "Core/ShaderManager.h"

#include <GraphicsModule.h>

namespace SamEngine
{
    ShaderManager::ShaderManager()
    {
        for (auto i = 0; i < MAX_SHADER_COUNT; ++i)
        {
            mInvalidID.push(i);
        }
    }

    void ShaderManager::Destroy()
    {
        for (auto i = 0; i < MAX_SHADER_COUNT; ++i)
        {
            if (mProgram[i] != InvalidResourceID)
            {
                GetGraphics().GetResourceManager().Destroy(mProgram[i]);
            }
        }
    }

    ShaderID ShaderManager::AddShader(const std::string &vertexSource, const std::string &fragmentSource)
    {
        ShaderID id = InvalidShaderID;
        if (!mInvalidID.empty())
        {
            id = mInvalidID.front();
            mInvalidID.pop();
            auto vsConfig = ShaderConfig::FromSource(ShaderType::VERTEX_SHADER, vertexSource);
            auto fsConfig = ShaderConfig::FromSource(ShaderType::FRAGMENT_SHADER, fragmentSource);
            auto vs = GetGraphics().GetResourceManager().Create(vsConfig, nullptr);
            auto fs = GetGraphics().GetResourceManager().Create(fsConfig, nullptr);
            auto programConfig = ProgramConfig::FromShader(vs, fs);
            mProgram[id] = GetGraphics().GetResourceManager().Create(programConfig, nullptr);
            GetGraphics().GetResourceManager().Destroy(vs);
            GetGraphics().GetResourceManager().Destroy(fs);
        }
        return id;
    }

    void ShaderManager::DeleteShader(ShaderID id)
    {
        s_assert(id != InvalidShaderID);
        s_assert_range(id, 0, MAX_SHADER_COUNT - 1);
        GetGraphics().GetResourceManager().Destroy(mProgram[id]);
        mInvalidID.push(id);
    }

    void ShaderManager::UseShader(ShaderID id)
    {
        s_assert(id != InvalidShaderID);
        s_assert_range(id, 0, MAX_SHADER_COUNT - 1);
        GetGraphics().GetRenderer().ApplyProgram(mProgram[id]);
    }

    ResourceID ShaderManager::GetProgram(ShaderID id)
    {
        s_assert(id != InvalidShaderID);
        s_assert_range(id, 0, MAX_SHADER_COUNT - 1);
        return mProgram[id];
    }
}