#pragma once

#if defined(SAM_WIN32) || defined(SAM_APPLE)
#    include "graphics/gl/gl_mesh_factory.h"
namespace sam
{
    typedef gl_mesh_factory mesh_factory;
}
#endif