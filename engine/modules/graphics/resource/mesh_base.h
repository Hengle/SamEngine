#pragma once

#include "graphics/attribute/index_buffer_attribute.h"
#include "graphics/attribute/vertex_buffer_attribute.h"

#include <vector>

namespace sam
{
    class mesh_base
    {
    public:
        index_buffer_attribute indices;

        vertex_buffer_attribute vertices;

        draw_type draws[graphics_const::max_draw_type];

        uint32 draw_count;
    };
}