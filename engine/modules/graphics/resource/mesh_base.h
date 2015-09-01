#pragma once

#include "graphics/attribute/index_buffer_attribute.h"
#include "graphics/attribute/vertex_buffer_attribute.h"
#include "graphics/config/mesh_config.h"

#include <resource/resource.h>

namespace sam
{
    class mesh_base : public resource_base<mesh_config>
    {
    public:
        index_buffer_attribute indices;

        vertex_buffer_attribute vertices;

        draw_type draws[graphics_config::max_draw_count];

        uint32 draw_count;

        void finalize() override;
    };

    inline void mesh_base::finalize()
    {
        indices = index_buffer_attribute();
        vertices = vertex_buffer_attribute();
        draw_count = 0;
        resource_base::finalize();
    }
}