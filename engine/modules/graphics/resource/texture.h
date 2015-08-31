#pragma once

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "graphics/gl/gl_texture.h"
namespace sam
{
    typedef gl_texture texture;
}
#endif