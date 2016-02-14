#if SAM_ANDROID

#include "EGLMouse.h"

namespace SamEngine
{
    void EGLMouse::SetCursorMode(MouseCursorMode mode)
    {

    }

    bool EGLMouse::IsButtonPressed(MouseButtonType type)
    {
        return false;
    }

    bool EGLMouse::IsButtonReleased(MouseButtonType type)
    {
        return false;
    }

    glm::vec2 EGLMouse::GetCursorPosition()
    {
        return glm::vec2();
    }
}

#endif