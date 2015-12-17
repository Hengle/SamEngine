#include "GLFWKeyboard.h"

namespace SamEngine
{
    GLFWKeyboard *GLFWKeyboard::self = nullptr;

    void GLFWKeyboard::Initialize(GLFWwindow *window)
    {
        s_assert(self == nullptr);
        s_assert(window != nullptr);
        self = this;
        mWindow = window;
        mTickID = GetThread().GetTicker().Add(this);
        glfwSetKeyCallback(mWindow, onKeyboardButtonEvent);
    }

    void GLFWKeyboard::Finalize()
    {
        s_assert(self != nullptr);
        GetThread().GetTicker().Remove(mTickID);
        self = nullptr;
    }

    bool GLFWKeyboard::IsKeyPressed(KeyboardButtonType type)
    {
        return mKeyPressedStateCache.test(static_cast<uint8>(type));
    }

    bool GLFWKeyboard::IsKeyReleased(KeyboardButtonType type)
    {
        return mKeyReleasedStateCache.test(static_cast<uint8>(type));
    }

    bool GLFWKeyboard::IsKeyRepeat(KeyboardButtonType type)
    {
        return mKeyRepeatStateCache.test(static_cast<uint8>(type));
    }

    void GLFWKeyboard::Tick(TickCount now, TickCount delta)
    {
        mKeyPressedStateCache.reset();
        mKeyReleasedStateCache.reset();
        mKeyRepeatStateCache.reset();
    }

    void GLFWKeyboard::onKeyboardButtonEvent(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        s_assert(self != nullptr);
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
        std::bitset<static_cast<uint8>(KeyboardButtonType::COUNT)> *targetCache = nullptr;
        switch (action)
        {
            case GLFW_PRESS:
                targetCache = &self->mKeyPressedStateCache;
                break;
            case GLFW_RELEASE:
                targetCache = &self->mKeyReleasedStateCache;
                break;
            case GLFW_REPEAT:
                targetCache = &self->mKeyRepeatStateCache;
                break;
        }
        if (targetCache)
        {
            targetCache->set(static_cast<uint8>(type));
        }
    }
}