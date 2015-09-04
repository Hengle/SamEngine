#pragma once

#include "gl.h"
#include "graphics/resource/graphics_resource_base.h"

namespace sam
{
    class gl_mesh : public mesh_base
    {
    public:
        GLuint index_buffer;

        GLuint vertex_buffer[graphics_config::max_stream_vertex_buffer_count];

        uint32 vertex_buffer_count{ 1 };

        uint32 current_vertex_buffer{ 0 };

        gl_vertex_attribute vertex_attribute[graphics_config::max_vertex_node_count];

        virtual void finalize() override;
    };

    inline void gl_mesh::finalize()
    {
        index_buffer = 0;
        std::memset(vertex_buffer, 0, sizeof(vertex_buffer));
        vertex_buffer_count = 1;
        current_vertex_buffer = 0;
        std::memset(vertex_attribute, 0, sizeof(vertex_attribute));
        mesh_base::finalize();
    }
}