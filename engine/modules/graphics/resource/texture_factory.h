#pragma once

#if defined(SAM_WIN32) || defined(SAM_APPLE)
#    include "graphics/gl/gl_texture_factory.h"
namespace sam
{
    typedef gl_texture_factory texture_factory;
}
#endif