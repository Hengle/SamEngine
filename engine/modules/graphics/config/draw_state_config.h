#pragma once

#include <resource/resource_name.h>

namespace sam
{
    class draw_state_config
    {
    public:
        static draw_state_config from_mesh_and_shader(resource::id mesh, resource::id shader);

        resource_name name{ resource_name::unique() };

        blend_state blend_state;

        depth_stencil_state depth_stencil_state;

        rasterizer_state rasterizer_state;

        color blend_colr{ 1.0f, 1.0f, 1.0f, 1.0f};

        resource::id mesh{ resource::invalid_id };

        resource::id shader{ resource::invalid_id };
    };

    inline draw_state_config draw_state_config::from_mesh_and_shader(resource::id mesh, resource::id shader)
    {
        draw_state_config config;
        config.mesh = mesh;
        config.shader = shader;
        return config;
    }
}