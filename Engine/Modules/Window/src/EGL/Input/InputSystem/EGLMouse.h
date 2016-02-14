#pragma once

#if SAM_ANDROID

#include "Input/InputSystem/IMouse.h"

namespace SamEngine
{
    class EGLMouse : public IMouse
    {
    public:
        virtual void SetCursorMode(MouseCursorMode mode) override;

        virtual bool IsButtonPressed(MouseButtonType type) override;

        virtual bool IsButtonReleased(MouseButtonType type) override;

        virtual glm::vec2 GetCursorPosition() override;
    };
}

#endif