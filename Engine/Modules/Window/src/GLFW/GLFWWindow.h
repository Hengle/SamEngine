#pragma once

#include "IWindow.h"

#include <GLFW/glfw3.h>

namespace SamEngine
{
    class GLFWWindow : public IWindow, public ITick
    {
    public:
        void Initialize(const WindowConfig &config) override;

        void Finalize() override;

        bool Available() override;

        bool ShouldClose() override;

        void Present() override;

        void SetMouseInputCallback(MouseInputCallback callback) override;

        void SetKeyboardInputCallback(KeyboardInputCallback callback) override;

        const WindowConfig &GetConfig() const override;

        void Tick(TickCount now, TickCount delta) override;

    protected:
        static void ErrorCallback(int error, const char *desc);

        static void MouseCallback(GLFWwindow *window, int button, int action, int mods);

        static void KeyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

    private:
        static GLFWWindow *self;
        WindowConfig mConfig;
        GLFWwindow *mWindow{ nullptr };
        TickID mTickID{ InvalidTickID };
        MouseInputCallback mMouseInputCallbck{ nullptr };
        KeyboardInputCallback mKeyboardInputCallback{ nullptr };
    };
}