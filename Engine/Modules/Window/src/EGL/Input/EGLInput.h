#pragma once

#if SAM_ANDROID

#include "Input/IInput.h"

#include "EGL/Input/InputSystem/EGLKeyboard.h"
#include "EGL/Input/InputSystem/EGLMouse.h"

namespace SamEngine
{
    class EGLInput : public IInput
    {
    public:
        virtual IKeyboard &GetKeyboard() override;

        virtual IMouse &GetMouse() override;

    private:
        EGLKeyboard mKeyboard;
        EGLMouse mMouse;
    };
}

#endif