#pragma once

#include "Texture.h"

#include <GraphicsModule.h>

#include <vector>

namespace SamEngine
{
    class ASSET_API Shader
    {
    public:
        CREATE_FUNC_DECLARE(Shader)

        Shader(const std::string &vertex, const std::string &fragment, const std::vector<std::pair<std::string, UniformAttributeFormat>> &uniforms);

        virtual ~Shader();

        void Apply();

        template <typename TYPE>
        void SetUniformData(int32 index, const TYPE &data);

        template <typename TYPE>
        void SetUniformData(const std::string &name, const TYPE &data);

    private:
        ResourceID mResourceID{ InvalidResourceID };
    };

    typedef std::shared_ptr<Shader> ShaderPtr;

    template <typename TYPE>
    void Shader::SetUniformData(int32 index, const TYPE &data)
    {
        GetGraphics().GetResourceManager().SetProgramUniformData(mResourceID, index, reinterpret_cast<const void *>(&data), sizeof(TYPE));
    }

    template <>
    inline void Shader::SetUniformData(int32 index, const Texture &data)
    {
        GetGraphics().GetResourceManager().SetProgramUniformData(mResourceID, index, reinterpret_cast<const void *>(&data.GetResourceID()), sizeof(ResourceID));
    }

    template <>
    inline void Shader::SetUniformData(int32 index, const TexturePtr &data)
    {
        GetGraphics().GetResourceManager().SetProgramUniformData(mResourceID, index, reinterpret_cast<const void *>(&data->GetResourceID()), sizeof(ResourceID));
    }

    template <typename TYPE>
    void Shader::SetUniformData(const std::string &name, const TYPE &data)
    {
        auto config = GetGraphics().GetResourceManager().GetProgramConfig(mResourceID);
        auto length = config.UniformLayout.Length();
        for (auto i = 0; i < length; ++i)
        {
            if (config.UniformLayout.At(i).GetName() == name)
            {
                SetUniformData(i, data);
                break;
            }
        }
    }
}