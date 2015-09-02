#pragma once

#include <core/class.h>
#include <resource/resource_name.h>

namespace sam
{
    class shader_config
    {
    public:
        CREATE_FUNC_DECLARE(shader_config)

        resource_name name{ resource_name::unique() };
    };
}