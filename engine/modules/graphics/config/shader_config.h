#pragma once

#include <resource/resource_name.h>

namespace sam
{
    class shader_config
    {
    public:
        resource_name name{ resource_name::unique() };
    };
}