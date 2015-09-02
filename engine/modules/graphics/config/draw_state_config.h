#pragma once

#include <resource/resource_name.h>

namespace sam
{
    class draw_state_config
    {
    public:
        resource_name name{ resource_name::unique() };
    };
}