#pragma once

#if defined(SAM_WIN32) || defined(SAM_APPLE)
#    include "glfw/glfw_window.h"
namespace sam
{
    typedef glfw_window window;
}
#endif