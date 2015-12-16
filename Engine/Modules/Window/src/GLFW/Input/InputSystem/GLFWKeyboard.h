#pragma once

#include "Input/InputSystem/IKeyboard.h"

#include "GLFW/glfw3.h"

#include <memory>

namespace SamEngine
{
    class GLFWKeyboard : public IKeyboard
    {
    public:
        void Initialize(GLFWwindow *window);

        void Finalize();
    };
}