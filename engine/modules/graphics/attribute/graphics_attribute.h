#pragma once

namespace sam
{
    class renderer;

    class mesh_pool;
    class shader_pool;
    class texture_pool;
    class draw_state_pool;

    class graphics_attribute
    {
    public:
        renderer *renderer{ nullptr };

        mesh_pool *mesh_pool{ nullptr };
        shader_pool *shader_pool{ nullptr };
        texture_pool *texture_pool{ nullptr };
        draw_state_pool *draw_state_pool{ nullptr };
    };
}