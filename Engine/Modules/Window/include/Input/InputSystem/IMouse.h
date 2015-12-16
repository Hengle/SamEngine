#pragma once

#include "WindowDefine.h"

namespace SamEngine
{
    class WINDOW_API IMouse
    {
    public:
        virtual ~IMouse() {}

        virtual void SetCursorMode(MouseCursorMode mode) = 0;

        virtual bool IsButtonPressed(MouseButtonType type) = 0;

        virtual bool IsButtonReleased(MouseButtonType type) = 0;
    };
}