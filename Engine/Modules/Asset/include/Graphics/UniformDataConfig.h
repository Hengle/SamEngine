#pragma once

#include <GraphicsModule.h>

namespace SamEngine
{
    class ASSET_API UniformDataConfig
    {
    public:
        explicit UniformDataConfig(ResourceID program);

        UniformLayout &Layout();

    private:
        UniformBufferConfig mConfig;

        friend class UniformData;
    };

    inline UniformDataConfig::UniformDataConfig(ResourceID program)
    {
        mConfig.Program = program;
    }

    inline UniformLayout &UniformDataConfig::Layout()
    {
        return mConfig.Layout;
    }
}