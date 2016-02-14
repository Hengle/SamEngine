#pragma once

#if SAM_ANDROID

#include "Input/InputSystem/IKeyboard.h"

namespace SamEngine
{
    class EGLKeyboard : public IKeyboard
    {
    public:
        virtual bool IsKeyPressed(KeyboardButtonType type) override;

        virtual bool IsKeyReleased(KeyboardButtonType type) override;

        virtual bool IsKeyRepeat(KeyboardButtonType type) override;
    };
}

#endif