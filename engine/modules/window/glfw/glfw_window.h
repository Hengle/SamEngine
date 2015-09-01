#pragma once

#include "window/core/window_base.h"

#include <GLFW/glfw3.h>

namespace sam
{
    class glfw_window : public window_base
    {
    public:
        glfw_window();

        virtual ~glfw_window();

        virtual void initialize(const window_config &config) override;

        virtual void finalize() override;

        virtual bool available() override;

        virtual bool should_close() override;

        void handle_event() override;

        virtual void present() override;

    protected:
        static void error_callback(int error, const char *desc);

    private:
        GLFWwindow *glfw_window_ptr{ nullptr };
    };
}