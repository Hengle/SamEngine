#pragma once

#include "graphics/core/window_base.h"

#include "graphics/gl/gl.h"

#include <GLFW/glfw3.h>

namespace sam
{
    class glfw_window : public window_base
    {
    public:
        glfw_window();

        virtual ~glfw_window();

        virtual void initialize(const graphics_config &config, const graphics_attribute &attribute) override;

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