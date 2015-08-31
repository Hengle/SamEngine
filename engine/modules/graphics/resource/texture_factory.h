#pragma once

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "graphics/gl/gl_texture_factory.h"
namespace sam
{
    typedef gl_texture_factory texture_factory;
}
#endif