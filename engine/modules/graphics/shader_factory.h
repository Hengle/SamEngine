#pragma once

#if defined(SAM_WIN32) || defined(SAM_APPLE)
#    include "gl/gl_shader_factory.h"
namespace sam
{
    typedef gl_shader_factory shader_factory;
}
#endif