#pragma once

#include "gl.h"
#include "graphics/resource/mesh_base.h"

namespace sam
{
    class gl_mesh : public mesh_base
    {
    public:
        GLuint index_buffer;

        GLuint vertex_buffer;

        void finalize() override;
    };
}