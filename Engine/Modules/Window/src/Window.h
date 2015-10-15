#if SAM_WINDOWS || SAM_OSX || SAM_LINUX
#    include "GLFW/GLFWWindow.h"
#endif

namespace SamEngine
{
#if SAM_WINDOWS || SAM_OSX || SAM_LINUX
    class Window : public GLFWWindow {};
#endif

    inline WINDOW_API IWindow &GetWindow()
    {
        static Window instance;
        return instance;
    }
}