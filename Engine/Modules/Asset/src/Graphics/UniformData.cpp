#include "Graphics/UniformData.h"

namespace SamEngine
{
    void UniformData::Create(UniformDataConfig &config)
    {
        mUniformBuffer = GetGraphics().GetResourceManager().Create(config.mConfig, nullptr);
    }

    void UniformData::Destroy()
    {
        if (mUniformBuffer != InvalidResourceID)
        {
            GetGraphics().GetResourceManager().Destroy(mUniformBuffer);
        }
    }

    void UniformData::Apply()
    {
        if (mUniformBuffer != InvalidResourceID)
        {
            GetGraphics().GetRenderer().ApplyUniformBuffer(mUniformBuffer);
        }
    }
}