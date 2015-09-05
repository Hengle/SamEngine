#include "glfw_window.h"

#include <core/assert.h>

namespace sam
{
    glfw_window::glfw_window() :
        window_base()
    {
    }

    glfw_window::~glfw_window()
    {
        if (glfw_window::available())
        {
            glfw_window::finalize();
        }
    }

    void glfw_window::initialize(const window_config &config)
    {
        s_assert(!available());
        if (glfwInit() != GL_TRUE)
        {
            s_error("glfw init error!\n");
        }
        glfwSetErrorCallback(error_callback);
        glfwWindowHint(GLFW_RED_BITS, channel_bits_of_format(config.color_format, pixel_channel_type::red));
        glfwWindowHint(GLFW_GREEN_BITS, channel_bits_of_format(config.color_format, pixel_channel_type::green));
        glfwWindowHint(GLFW_BLUE_BITS, channel_bits_of_format(config.color_format, pixel_channel_type::blue));
        glfwWindowHint(GLFW_ALPHA_BITS, channel_bits_of_format(config.color_format, pixel_channel_type::alpha));
        glfwWindowHint(GLFW_DEPTH_BITS, channel_bits_of_format(config.depth_format, pixel_channel_type::depth));
        glfwWindowHint(GLFW_STENCIL_BITS, channel_bits_of_format(config.depth_format, pixel_channel_type::stencil));
        glfwWindowHint(GLFW_SAMPLES, config.sample_count > 1 ? config.sample_count : 0);
        #if SAM_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        #endif
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfw_window_ptr = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);
        s_assert(available());
        glfwMakeContextCurrent(glfw_window_ptr);
        glfwSwapInterval(config.swap_interval);
    }

    void glfw_window::finalize()
    {
        s_assert(available());
        glfwDestroyWindow(glfw_window_ptr);
        glfw_window_ptr = nullptr;
        glfwTerminate();
    }

    bool glfw_window::available()
    {
        return glfw_window_ptr != nullptr;
    }

    bool glfw_window::should_close()
    {
        s_assert(available());
        return glfwWindowShouldClose(glfw_window_ptr) == GL_TRUE;
    }

    void glfw_window::handle_event()
    {
        s_assert(available());
        glfwPollEvents();
    }

    void glfw_window::present()
    {
        glfwSwapBuffers(glfw_window_ptr);
    }

    void glfw_window::error_callback(int error, const char *desc)
    {
        log::error("glfw error[%d]: %s\n", error, desc);
    }
}