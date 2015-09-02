#pragma once

#include "gl.h"

#include "graphics/resource/texture_base.h"

namespace sam
{
    class gl_texture : public texture_base
    {
    public:
        GLuint texture{ 0 };

        GLenum target{ 0 };

        GLuint frame_buffer{ 0 };

        GLuint depth_render_buffer{ 0 };

        virtual void finalize() override;
    };

    inline void gl_texture::finalize()
    {
        texture = 0;
        target = 0;
        frame_buffer = 0;
        depth_render_buffer = 0;
        texture_base::finalize();
    }
}