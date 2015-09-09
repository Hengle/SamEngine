#pragma once

#include "graphics/config/graphics_config.h"
#include "graphics/resource/graphics_resource_base.h"

namespace sam
{
    class gl_shader : public shader_base
    {
    public:
        GLuint program{ 0 };

        int32 texture_index[graphics_config::max_uniform_node_count];

        GLint uniform_locations[graphics_config::max_uniform_node_count];

        virtual void finalize() override;
    };

    inline void gl_shader::finalize()
    {
        program = 0;
        std::memset(texture_index, 0, sizeof(texture_index));
        std::memset(uniform_locations, 0, sizeof(uniform_locations));
        shader_base::finalize();
    }
}