#pragma once

#include <GraphicsDefine.h>

#include <string>

namespace SamEngine
{
    struct GRAPHICS_API ShaderConfig
    {
        static ShaderConfig FromSource(ShaderType type, const std::string &source);

        ResourceName Name{ ResourceName::Unique() };

        std::string Source;

        ShaderType Type{ ShaderType::VERTEX_SHADER };
    };

    inline ShaderConfig ShaderConfig::FromSource(ShaderType type, const std::string &source)
    {
        ShaderConfig config;
        config.Type = type;
        config.Source = source;
        return config;
    }
}