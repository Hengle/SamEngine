#pragma once

#include "GraphicsDefine.h"

namespace SamEngine
{
    struct GRAPHICS_API ProgramConfig
    {
        static ProgramConfig FromShader(ResourceID vertex, ResourceID fragment);

        ResourceName Name{ ResourceName::Unique() };

        ResourceID VertexShader{ InvalidResourceID };

        ResourceID FragmentShader{ InvalidResourceID };
    };

    inline ProgramConfig ProgramConfig::FromShader(ResourceID vertex, ResourceID fragment)
    {
        ProgramConfig config;
        config.VertexShader = vertex;
        config.FragmentShader = fragment;
        return config;
    }
}