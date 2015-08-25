#pragma once

#include "gl.h"

#include "graphics/core/texture_base.h"

namespace sam
{
    class gl_texture : public texture_base
    {
    public:
        gl_texture();

        virtual ~gl_texture();

        virtual void finalize() override;

    private:
        GLuint texture;
    };
}