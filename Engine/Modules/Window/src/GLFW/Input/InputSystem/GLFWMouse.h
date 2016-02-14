#pragma once

#if SAM_WINDOWS || SAM_OSX || SAM_LINUX

#include "WindowDefine.h"
#include "Input/InputSystem/IMouse.h"

#include "GLFW/glfw3.h"

#include <bitset>
#include <memory>

namespace SamEngine
{
    class GLFWMouse : public IMouse, public ITick
    {
    public:
        void Initialize(GLFWwindow *window);

        void Finalize();

        virtual void SetCursorMode(MouseCursorMode mode) override;

        virtual bool IsButtonPressed(MouseButtonType type) override;

        virtual bool IsButtonReleased(MouseButtonType type) override;

        virtual glm::vec2 GetCursorPosition() override;

        virtual void Tick(TickCount now, TickCount delta) override;

    private:
        static void onMouseButtonEvent(GLFWwindow *window, int button, int action, int mods);

    private:
        static GLFWMouse *self;
        GLFWwindow *mWindow{ nullptr };
        TickID mTickID{ InvalidTickID };
        std::bitset<static_cast<uint8>(MouseButtonType::COUNT)> mButtonPressedStateCache;
        std::bitset<static_cast<uint8>(MouseButtonType::COUNT)> mButtonReleasedStateCache;
    };
}

#endif