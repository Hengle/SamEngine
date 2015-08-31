#pragma once

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "graphics/glfw/glfw_window.h"
namespace sam
{
    typedef glfw_window window;
}
#endif