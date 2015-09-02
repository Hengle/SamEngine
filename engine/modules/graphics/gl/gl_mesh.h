#pragma once

#include "gl.h"
#include "graphics/resource/mesh_base.h"

namespace sam
{
    class gl_mesh : public mesh_base
    {
    public:
        GLuint index_buffer;

        GLuint vertex_buffer[graphics_config::max_stream_vertex_buffer_count];

        uint32 vertex_buffer_count{ 1 };

        uint32 current_vertex_buffer{ 0 };

        void finalize() override;
    };

    inline void gl_mesh::finalize()
    {
        index_buffer = 0;
        vertex_buffer_count = 1;
        current_vertex_buffer = 0;
        mesh_base::finalize();
    }
}