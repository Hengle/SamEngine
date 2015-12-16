#pragma once

#include "Input/IInput.h"

#include "GLFW/Input/InputSystem/GLFWKeyboard.h"
#include "GLFW/Input/InputSystem/GLFWMouse.h"

#include <GLFW/glfw3.h>

namespace SamEngine
{
    class GLFWInput : public IInput
    {
    public:
        void Initialize(GLFWwindow *window);

        void Finalize();

        virtual IKeyboard &GetKeyboard() override;

        virtual IMouse &GetMouse() override;

    private:
        GLFWKeyboard mKeyboard;
        GLFWMouse mMouse;
    };
}