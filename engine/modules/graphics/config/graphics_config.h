#pragma once

#include <core/types.h>

namespace sam
{
    class graphics_config
    {
    public:
        static const uint32 max_uniform_node = 16;

        static const uint32 max_vertex_node = 16;

        static const uint32 max_draw_type = 8;

        int32 registry_size{ 256 };

        int32 texture_pool_size{ 256 };
    };
}