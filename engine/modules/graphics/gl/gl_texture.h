#pragma once

#include "gl.h"

#include "graphics/resource/texture_base.h"

namespace sam
{
    class gl_texture : public texture_base
    {
        friend class gl_renderer;
    public:
        gl_texture();

        virtual ~gl_texture();

        virtual void finalize() override;

    private:
        GLuint texture{ 0 };
    };
}