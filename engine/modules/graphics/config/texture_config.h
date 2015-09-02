#pragma once

#include <core/types.h>

#include <core/class.h>
#include <resource/resource_name.h>

namespace sam
{
    class texture_config
    {
    public:
        CREATE_FUNC_DECLARE(texture_config)

        resource_name name { resource_name::unique() };

        int32 width{ 0 };

        int32 height{ 0 };
    };
}