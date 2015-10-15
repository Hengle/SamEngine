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

        const WindowConfig &GetConfig() const override;

        void Tick(TickCount now, TickCount delta) override;

    protected:
        static void ErrorCallback(int error, const char *desc);

    private:
        WindowConfig mConfig;
        GLFWwindow *mWindow{ nullptr };
        TickID mTickID{ InvalidTickID };
    };
}