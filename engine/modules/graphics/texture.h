#pragma once

#if defined(SAM_WIN32) || defined(SAM_APPLE)
#    include "gl/gl_texture.h"
namespace sam
{
    typedef gl_texture texture;
}
#endif