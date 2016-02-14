#pragma once

#if SAM_WINDOWS || SAM_OSX || SAM_LINUX

#include "WindowDefine.h"
#include "Input/InputSystem/IKeyboard.h"

#include "GLFW/glfw3.h"

#include <bitset>
#include <memory>

namespace SamEngine
{
    class GLFWKeyboard : public IKeyboard, public ITick
    {
    public:
        void Initialize(GLFWwindow *window);

        void Finalize();

        virtual bool IsKeyPressed(KeyboardButtonType type) override;

        virtual bool IsKeyReleased(KeyboardButtonType type) override;

        virtual bool IsKeyRepeat(KeyboardButtonType type) override;

        virtual void Tick(TickCount now, TickCount delta) override;

    private:
        static void onKeyboardButtonEvent(GLFWwindow *window, int key, int scancode, int action, int mods);

    private:
        static GLFWKeyboard *self;
        GLFWwindow *mWindow{ nullptr };
        TickID mTickID{ InvalidTickID };
        std::bitset<static_cast<uint8>(KeyboardButtonType::COUNT)> mKeyPressedStateCache;
        std::bitset<static_cast<uint8>(KeyboardButtonType::COUNT)> mKeyReleasedStateCache;
        std::bitset<static_cast<uint8>(KeyboardButtonType::COUNT)> mKeyRepeatStateCache;
    };
}

#endif