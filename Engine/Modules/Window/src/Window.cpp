#include "Window.h"

namespace SamEngine
{
    WINDOW_API IWindow &GetWindow()
    {
        static Window instance;
        return instance;
    }
}