#pragma once

#include <core/types.h>

namespace sam
{
    class graphics_config
    {
    public:
        static const uint32 cube_texture_face_count = 6;

        static const uint32 max_texture_mipmap_count = 12;

        static const uint32 max_texture_count = 16;

        static const uint32 max_uniform_node_count = 16;

        static const uint32 max_vertex_node_count = 16;

        static const uint32 max_draw_count = 8;

        static const uint32 max_stream_vertex_buffer_count = 2;

        int32 registry_size{ 256 };

        int32 mesh_pool_size{ 128 };

        int32 shader_pool_size{ 128 };

        int32 texture_pool_size{ 128 };

        int32 draw_state_pool_size{ 128 };
    };
}