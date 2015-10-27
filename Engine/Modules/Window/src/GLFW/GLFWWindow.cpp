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
            s_error("glfw init error!\n");
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
        glfwSetMouseButtonCallback(mWindow, MouseCallback);
        glfwSetKeyCallback(mWindow, KeyboardCallback);
        glfwMakeContextCurrent(mWindow);
        glfwSwapInterval(mConfig.SwapInterval);
        mTickID = GetThread().GetTicker().Add(this);
    }

    void GLFWWindow::Finalize()
    {
        s_assert(Available());
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

    void GLFWWindow::SetMouseInputCallback(MouseInputCallback callback)
    {
        mMouseInputCallbck = callback;
    }

    void GLFWWindow::SetKeyboardInputCallback(KeyboardInputCallback callback)
    {
        mKeyboardInputCallback = callback;
    }

    void GLFWWindow::SetTitle(const std::string &name)
    {
        glfwSetWindowTitle(mWindow, name.c_str());
    }

    void GLFWWindow::ErrorCallback(int error, const char *desc)
    {
        GetLog().Error("glfw error[%d]: %s\n", error, desc);
    }

    void GLFWWindow::MouseCallback(GLFWwindow *window, int button, int action, int mods)
    {
        if (self != nullptr && self->mMouseInputCallbck != nullptr)
        {
            auto type = MouseButtonType::LEFT;
            if (button == GLFW_MOUSE_BUTTON_RIGHT)
            {
                type = MouseButtonType::RIGHT;
            }
            else if (button == GLFW_MOUSE_BUTTON_MIDDLE)
            {
                type = MouseButtonType::MIDDLE;
            }
            self->mMouseInputCallbck(type, action == GLFW_PRESS);
        }
    }

    void GLFWWindow::KeyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (self != nullptr && self->mMouseInputCallbck != nullptr)
        {
            auto type = KeyboardButtonType::UNKNOWN;
            switch (key)
            {
            case GLFW_KEY_ESCAPE:
                type = KeyboardButtonType::ESC;
                break;
            case GLFW_KEY_F1:
                type = KeyboardButtonType::F1;
                break;
            case GLFW_KEY_F2:
                type = KeyboardButtonType::F2;
                break;
            case GLFW_KEY_F3:
                type = KeyboardButtonType::F3;
                break;
            case GLFW_KEY_F4:
                type = KeyboardButtonType::F4;
                break;
            case GLFW_KEY_F5:
                type = KeyboardButtonType::F5;
                break;
            case GLFW_KEY_F6:
                type = KeyboardButtonType::F6;
                break;
            case GLFW_KEY_F7:
                type = KeyboardButtonType::F7;
                break;
            case GLFW_KEY_F8:
                type = KeyboardButtonType::F8;
                break;
            case GLFW_KEY_F9:
                type = KeyboardButtonType::F9;
                break;
            case GLFW_KEY_F10:
                type = KeyboardButtonType::F10;
                break;
            case GLFW_KEY_F11:
                type = KeyboardButtonType::F11;
                break;
            case GLFW_KEY_F12:
                type = KeyboardButtonType::F12;
                break;
            case GLFW_KEY_1:
                type = KeyboardButtonType::NUM_1;
                break;
            case GLFW_KEY_2:
                type = KeyboardButtonType::NUM_2;
                break;
            case GLFW_KEY_3:
                type = KeyboardButtonType::NUM_3;
                break;
            case GLFW_KEY_4:
                type = KeyboardButtonType::NUM_4;
                break;
            case GLFW_KEY_5:
                type = KeyboardButtonType::NUM_5;
                break;
            case GLFW_KEY_6:
                type = KeyboardButtonType::NUM_6;
                break;
            case GLFW_KEY_7:
                type = KeyboardButtonType::NUM_7;
                break;
            case GLFW_KEY_8:
                type = KeyboardButtonType::NUM_8;
                break;
            case GLFW_KEY_9:
                type = KeyboardButtonType::NUM_9;
                break;
            case GLFW_KEY_0:
                type = KeyboardButtonType::NUM_0;
                break;
            case GLFW_KEY_KP_1:
                type = KeyboardButtonType::NUM_PAD_1;
                break;
            case GLFW_KEY_KP_2:
                type = KeyboardButtonType::NUM_PAD_2;
                break;
            case GLFW_KEY_KP_3:
                type = KeyboardButtonType::NUM_PAD_3;
                break;
            case GLFW_KEY_KP_4:
                type = KeyboardButtonType::NUM_PAD_4;
                break;
            case GLFW_KEY_KP_5:
                type = KeyboardButtonType::NUM_PAD_5;
                break;
            case GLFW_KEY_KP_6:
                type = KeyboardButtonType::NUM_PAD_6;
                break;
            case GLFW_KEY_KP_7:
                type = KeyboardButtonType::NUM_PAD_7;
                break;
            case GLFW_KEY_KP_8:
                type = KeyboardButtonType::NUM_PAD_8;
                break;
            case GLFW_KEY_KP_9:
                type = KeyboardButtonType::NUM_PAD_9;
                break;
            case GLFW_KEY_KP_0:
                type = KeyboardButtonType::NUM_PAD_0;
                break;
            case GLFW_KEY_A:
                type = KeyboardButtonType::A;
                break;
            case GLFW_KEY_B:
                type = KeyboardButtonType::B;
                break;
            case GLFW_KEY_C:
                type = KeyboardButtonType::C;
                break;
            case GLFW_KEY_D:
                type = KeyboardButtonType::D;
                break;
            case GLFW_KEY_E:
                type = KeyboardButtonType::E;
                break;
            case GLFW_KEY_F:
                type = KeyboardButtonType::F;
                break;
            case GLFW_KEY_G:
                type = KeyboardButtonType::G;
                break;
            case GLFW_KEY_H:
                type = KeyboardButtonType::H;
                break;
            case GLFW_KEY_I:
                type = KeyboardButtonType::I;
                break;
            case GLFW_KEY_J:
                type = KeyboardButtonType::J;
                break;
            case GLFW_KEY_K:
                type = KeyboardButtonType::K;
                break;
            case GLFW_KEY_L:
                type = KeyboardButtonType::L;
                break;
            case GLFW_KEY_M:
                type = KeyboardButtonType::M;
                break;
            case GLFW_KEY_N:
                type = KeyboardButtonType::N;
                break;
            case GLFW_KEY_O:
                type = KeyboardButtonType::O;
                break;
            case GLFW_KEY_P:
                type = KeyboardButtonType::P;
                break;
            case GLFW_KEY_Q:
                type = KeyboardButtonType::Q;
                break;
            case GLFW_KEY_R:
                type = KeyboardButtonType::R;
                break;
            case GLFW_KEY_S:
                type = KeyboardButtonType::S;
                break;
            case GLFW_KEY_T:
                type = KeyboardButtonType::T;
                break;
            case GLFW_KEY_U:
                type = KeyboardButtonType::U;
                break;
            case GLFW_KEY_V:
                type = KeyboardButtonType::V;
                break;
            case GLFW_KEY_W:
                type = KeyboardButtonType::W;
                break;
            case GLFW_KEY_X:
                type = KeyboardButtonType::X;
                break;
            case GLFW_KEY_Y:
                type = KeyboardButtonType::Y;
                break;
            case GLFW_KEY_Z:
                type = KeyboardButtonType::Z;
                break;
            }
            self->mKeyboardInputCallback(type, action == GLFW_PRESS);
        }
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