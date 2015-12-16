#pragma once

#include "IWindow.h"

#include "Input/GLFWInput.h"

#include <GLFW/glfw3.h>

namespace SamEngine
{
    class GLFWWindow : public IWindow, public ITick
    {
    public:
        virtual void Initialize(const WindowConfig &config) override;

        virtual void Finalize() override;

        virtual bool Available() override;

        virtual bool ShouldClose() override;

        virtual void Present() override;

        virtual IInput &GetInput() override;

        virtual void SetTitle(const std::string &name) override;

        virtual const WindowConfig &GetConfig() const override;

        virtual void Tick(TickCount now, TickCount delta) override;

    protected:
        static void ErrorCallback(int error, const char *desc);

    private:
        static GLFWWindow *self;
        GLFWInput mInput;
        WindowConfig mConfig;
        GLFWwindow *mWindow{ nullptr };
        TickID mTickID{ InvalidTickID };
    };
}