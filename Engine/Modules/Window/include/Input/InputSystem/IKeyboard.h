#pragma once

#include "WindowDefine.h"

namespace SamEngine
{
    class WINDOW_API IKeyboard
    {
    public:
        virtual ~IKeyboard() {}

        virtual bool IsKeyPressed(KeyboardButtonType type) = 0;

        virtual bool IsKeyReleased(KeyboardButtonType type) = 0;

        virtual bool IsKeyRepeat(KeyboardButtonType type) = 0;
    };
}