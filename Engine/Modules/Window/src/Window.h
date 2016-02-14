#pragma once

#if SAM_WINDOWS || SAM_OSX || SAM_LINUX
#   include "GLFW/GLFWWindow.h"
#elif SAM_ANDROID
#   include "EGL/EGLWindow.h"
#endif

namespace SamEngine
{
#if SAM_WINDOWS || SAM_OSX || SAM_LINUX
    class Window : public GLFWWindow {};
#elif SAM_ANDROID
    class Window : public EGLWindow {};
#endif
}