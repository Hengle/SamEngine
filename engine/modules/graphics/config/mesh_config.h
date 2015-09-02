#pragma once

#include "graphics/core/define.h"
#include "graphics/core/vertex_layout.h"

#include <core/class.h>
#include <resource/resource_name.h>

namespace sam
{
    class mesh_config
    {
    public:
        CREATE_FUNC_DECLARE(mesh_config)

        explicit mesh_config(buffer_usage vertex = buffer_usage::immutable, buffer_usage index = buffer_usage::immutable);

        resource_name name{ resource_name::unique() };

        buffer_usage vertex_usage{ buffer_usage::immutable };
        vertex_layout vertex_layout;
        int32 vertex_count{ 0 };
        int32 vertex_offset{ 0 };

        buffer_usage index_usage{ buffer_usage::immutable };
        index_type index_type{ index_type::none };
        int32 index_count{ 0 };
        int32 index_offset{ 0 };

        draw_type draws[graphics_config::max_draw_count];
        int32 draw_count{ 0 };
    };

    inline mesh_config::mesh_config(buffer_usage vertex, buffer_usage index) :
        vertex_usage(vertex),
        index_usage(index)
    {
    }
}