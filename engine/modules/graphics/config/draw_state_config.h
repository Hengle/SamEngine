#pragma once

#include <core/class.h>
#include <resource/resource_name.h>

namespace sam
{
    class draw_state_config
    {
    public:
        CREATE_FUNC_DECLARE(draw_state_config)

        resource_name name{ resource_name::unique() };
    };
}