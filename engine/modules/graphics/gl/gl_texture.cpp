#include "gl_texture.h"

#include "core/assert.h"

namespace sam
{
    gl_texture::gl_texture()
    {
    }

    gl_texture::~gl_texture()
    {
        s_assert(texture == 0);
    }

    void gl_texture::finalize()
    {
        texture = 0;
        texture_base::finalize();
    }
}