#pragma once

#include "InputSystem/IKeyboard.h"
#include "InputSystem/IMouse.h"

#include <CoreModule.h>

namespace SamEngine
{
    class WINDOW_API IInput
    {
    public:
        virtual ~IInput() {}

        virtual IKeyboard &GetKeyboard() = 0;

        virtual IMouse &GetMouse() = 0;
    };
}