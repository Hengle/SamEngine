#if SAM_WINDOWS || SAM_OSX || SAM_LINUX

#include "GLFWWindow.h"

namespace SamEngine
{
    GLFWWindow *GLFWWindow::self = nullptr;

    void GLFWWindow::Initialize(const WindowConfig &config)
    {
        self = this;
        s_assert(!Available());
        mConfig = config;
        if (glfwInit() != GL_TRUE)
        {
            s_error("GLFW init error!\n");
        }
        glfwSetErrorCallback(ErrorCallback);
        glfwWindowHint(GLFW_RED_BITS, ChannelBitOfPixelFormat(mConfig.ColorFormat, PixelChannel::RED));
        glfwWindowHint(GLFW_GREEN_BITS, ChannelBitOfPixelFormat(mConfig.ColorFormat, PixelChannel::GREEN));
        glfwWindowHint(GLFW_BLUE_BITS, ChannelBitOfPixelFormat(mConfig.ColorFormat, PixelChannel::BLUE));
        glfwWindowHint(GLFW_ALPHA_BITS, ChannelBitOfPixelFormat(mConfig.ColorFormat, PixelChannel::ALPHA));
        glfwWindowHint(GLFW_DEPTH_BITS, ChannelBitOfPixelFormat(mConfig.DepthFormat, PixelChannel::DEPTH));
        glfwWindowHint(GLFW_STENCIL_BITS, ChannelBitOfPixelFormat(mConfig.DepthFormat, PixelChannel::STENCIL));
        glfwWindowHint(GLFW_SAMPLES, mConfig.SampleCount > 1 ? mConfig.SampleCount : 0);
        #if SAM_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        #endif
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        mWindow = glfwCreateWindow(mConfig.Width, mConfig.Height, mConfig.Title.c_str(), nullptr, nullptr);
        s_assert(Available());
        glfwMakeContextCurrent(mWindow);
        glfwSwapInterval(mConfig.SwapInterval);
        mInput.Initialize(mWindow);
        mTickID = GetThread().GetTicker().Add(this);
    }

    void GLFWWindow::Finalize()
    {
        s_assert(Available());
        mInput.Finalize();
        glfwDestroyWindow(mWindow);
        mWindow = nullptr;
        glfwTerminate();
        GetThread().GetTicker().Remove(mTickID);
        self = nullptr;
    }

    bool GLFWWindow::Available()
    {
        return mWindow != nullptr;
    }

    bool GLFWWindow::ShouldClose()
    {
        s_assert(Available());
        return glfwWindowShouldClose(mWindow) == GL_TRUE;
    }

    void GLFWWindow::Present()
    {
        glfwSwapBuffers(mWindow);
    }

    IInput &GLFWWindow::GetInput()
    {
        return mInput;
    }

    void GLFWWindow::SetTitle(const std::string &name)
    {
        glfwSetWindowTitle(mWindow, name.c_str());
    }

    void GLFWWindow::ErrorCallback(int error, const char *desc)
    {
        GetLog().Error("glfw error[%d]: %s\n", error, desc);
    }


    const WindowConfig &GLFWWindow::GetConfig() const
    {
        return mConfig;
    }

    void GLFWWindow::Tick(TickCount now, TickCount delta)
    {
        s_assert(Available());
        glfwPollEvents();
    }
}

#endif