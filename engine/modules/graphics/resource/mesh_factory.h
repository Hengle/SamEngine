#pragma once

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "graphics/gl/gl_mesh_factory.h"
namespace sam
{
    typedef gl_mesh_factory mesh_factory;
}
#endif