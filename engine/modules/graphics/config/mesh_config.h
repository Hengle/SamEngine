#pragma once

#include "graphics/attribute/draw_call_attribute.h"
#include "graphics/attribute/index_buffer_attribute.h"
#include "graphics/attribute/vertex_buffer_attribute.h"
#include "graphics/core/define.h"

#include <resource/resource_name.h>

namespace sam
{
    class mesh_config
    {
    public:
        static mesh_config from_data(buffer_usage vertex = buffer_usage::immutable, buffer_usage index = buffer_usage::immutable);

        resource_name name{ resource_name::unique() };

        vertex_buffer_attribute vertices;

        index_buffer_attribute indices;

        draw_call_attribute draw_calls;

        int32 vertex_buffer_offset{ 0 };

        int32 index_buffer_offset{ 0 };
    };

    inline mesh_config mesh_config::from_data(buffer_usage vertex, buffer_usage index)
    {
        mesh_config config;
        config.vertices.usage = vertex;
        config.indices.usage = index;
        return config;
    }
}