#include "GLFWInput.h"

#include <WindowModule.h>

namespace SamEngine
{
    void GLFWInput::Initialize(GLFWwindow *window)
    {
        mMouse.Initialize(window);
        mKeyboard.Initialize(window);
    }

    void GLFWInput::Finalize()
    {
        mMouse.Finalize();
        mKeyboard.Finalize();
    }

    IKeyboard &GLFWInput::GetKeyboard()
    {
        return mKeyboard;
    }

    IMouse &GLFWInput::GetMouse()
    {
        return mMouse;
    }
}