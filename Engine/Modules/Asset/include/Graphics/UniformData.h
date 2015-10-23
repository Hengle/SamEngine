#pragma once

#include "UniformDataConfig.h"
#include "Texture.h"

namespace SamEngine
{
    class ASSET_API UniformData
    {
    public:
        void Create(UniformDataConfig &config);

        void Destroy();

        void Apply();

        template <typename TYPE>
        void SetUniformData(int32 index, const TYPE &data);

        template <typename TYPE>
        void SetUniformData(const std::string &name, const TYPE &data);

    private:
        ResourceID mUniformBuffer{ InvalidResourceID };
    };

    template <typename TYPE>
    void UniformData::SetUniformData(int32 index, const TYPE &data)
    {
        GetGraphics().GetResourceManager().SetUniformBufferData(mUniformBuffer, index, reinterpret_cast<const void *>(&data), sizeof(TYPE));
    }

    template <>
    inline void UniformData::SetUniformData(int32 index, const Texture &data)
    {
        GetGraphics().GetResourceManager().SetUniformBufferData(mUniformBuffer, index, reinterpret_cast<const void *>(&data.mID), sizeof(ResourceID));
    }

    template <>
    inline void UniformData::SetUniformData(int32 index, const TexturePtr &data)
    {
        GetGraphics().GetResourceManager().SetUniformBufferData(mUniformBuffer, index, reinterpret_cast<const void *>(&data->mID), sizeof(ResourceID));
    }

    template <typename TYPE>
    void UniformData::SetUniformData(const std::string &name, const TYPE &data)
    {
        auto config = GetGraphics().GetResourceManager().GetUniformBufferConfig(mUniformBuffer);
        auto length = config.Layout.Length();
        for (auto i = 0; i < length; ++i)
        {
            if (config.Layout.At(i).GetName() == name)
            {
                SetUniformData(i, data);
                break;
            }
        }
    }
}