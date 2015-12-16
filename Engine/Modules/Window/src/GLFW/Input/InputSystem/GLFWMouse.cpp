#include "GLFWMouse.h"

#include <CoreModule.h>

namespace SamEngine
{
    GLFWMouse *GLFWMouse::self = nullptr;

    void GLFWMouse::Initialize(GLFWwindow *window)
    {
        s_assert(self == nullptr);
        s_assert(window != nullptr);
        self = this;
        mTickID = GetThread().GetTicker().Add(this);
        glfwSetMouseButtonCallback(window, onMouseButtonClick);
    }

    void GLFWMouse::Finalize()
    {
        s_assert(self != nullptr);
        GetThread().GetTicker().Remove(mTickID);
        self = nullptr;
    }

    void GLFWMouse::onMouseButtonClick(GLFWwindow *window, int button, int action, int mods)
    {
        s_assert(self != nullptr);
        auto type = MouseButtonType::UNKNOWN;
        switch (button)
        {
            case GLFW_MOUSE_BUTTON_LEFT:
                type = MouseButtonType::LEFT;
                break;
            case GLFW_MOUSE_BUTTON_RIGHT:
                type = MouseButtonType::RIGHT;
                break;
            case GLFW_MOUSE_BUTTON_MIDDLE:
                type = MouseButtonType::MIDDLE;
                break;
        }
        std::bitset<static_cast<uint8>(MouseButtonType::COUNT)> *targetCache = nullptr;
        switch (action)
        {
            case GLFW_PRESS:
                targetCache = &self->mButtonPressedStateCache;
                break;
            case GLFW_RELEASE:
                targetCache = &self->mButtonReleasedStateCache;
                break;
        }
        if (targetCache)
        {
            targetCache->set(static_cast<uint8>(type));
        }
    }

    void GLFWMouse::SetCursorMode(MouseCursorMode mode)
    {
        switch (mode)
        {
            case MouseCursorMode::NORMAL:
                glfwSetInputMode(self->mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                break;
            case MouseCursorMode::HIDDEN:
                glfwSetInputMode(self->mWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
                break;
            case MouseCursorMode::DISABLE:
                glfwSetInputMode(self->mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                break;
        }
    }

    bool GLFWMouse::IsButtonPressed(MouseButtonType type)
    {
        return mButtonPressedStateCache.test(static_cast<uint8>(type));
    }

    bool GLFWMouse::IsButtonReleased(MouseButtonType type)
    {
        return mButtonReleasedStateCache.test(static_cast<uint8>(type));
    }

    void GLFWMouse::Tick(TickCount now, TickCount delta)
    {
        mButtonPressedStateCache.reset();
        mButtonReleasedStateCache.reset();
    }
}