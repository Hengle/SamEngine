#if SAM_ANDROID

#include "EGLKeyboard.h"

namespace SamEngine
{
    bool EGLKeyboard::IsKeyPressed(KeyboardButtonType type)
    {
        return false;
    }

    bool EGLKeyboard::IsKeyReleased(KeyboardButtonType type)
    {
        return false;
    }

    bool EGLKeyboard::IsKeyRepeat(KeyboardButtonType type)
    {
        return false;
    }
}

#endif