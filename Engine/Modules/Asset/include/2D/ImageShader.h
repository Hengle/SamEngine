#pragma once

#include "Graphics/Texture.h"

#include <GraphicsModule.h>

namespace SamEngine
{
    class ASSET_API ImageShader
    {
    public:
        static void Initialize();

        static void Finalize();

        static void Apply();

        template <typename TYPE>
        static void SetUniformData(int32 index, const TYPE &data);

        template <typename TYPE>
        static void SetUniformData(const std::string &name, const TYPE &data);

    private:
        static ResourceID mResourceID;
    };


    template <typename TYPE>
    void ImageShader::SetUniformData(int32 index, const TYPE &data)
    {
        GetGraphics().GetResourceManager().SetProgramUniformData(mResourceID, index, reinterpret_cast<const void *>(&data), sizeof(TYPE));
    }

    template <>
    inline void ImageShader::SetUniformData(int32 index, const Texture &data)
    {
        GetGraphics().GetResourceManager().SetProgramUniformData(mResourceID, index, reinterpret_cast<const void *>(&data.mID), sizeof(ResourceID));
    }

    template <>
    inline void ImageShader::SetUniformData(int32 index, const TexturePtr &data)
    {
        GetGraphics().GetResourceManager().SetProgramUniformData(mResourceID, index, reinterpret_cast<const void *>(&data->mID), sizeof(ResourceID));
    }

    template <typename TYPE>
    void ImageShader::SetUniformData(const std::string &name, const TYPE &data)
    {
        auto config = GetGraphics().GetResourceManager().GetProgramConfig(mUniformBuffer);
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