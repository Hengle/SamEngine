#include "glfw_window.h"

#include "core/assert.h"

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

    void glfw_window::initialize(const graphics_config &config, const graphics_attribute &attribute)
    {
        s_assert(!available());
        window_base::initialize(config, attribute);
        if (glfwInit() != GL_TRUE)
        {
            s_error("glfw init error!\n");
        }
        glfwSetErrorCallback(error_callback);
        glfwWindowHint(GLFW_RED_BITS, channel_bits_of_format(render_target_attribute.color_format, pixel_channel::red));
        glfwWindowHint(GLFW_GREEN_BITS, channel_bits_of_format(render_target_attribute.color_format, pixel_channel::green));
        glfwWindowHint(GLFW_BLUE_BITS, channel_bits_of_format(render_target_attribute.color_format, pixel_channel::blue));
        glfwWindowHint(GLFW_ALPHA_BITS, channel_bits_of_format(render_target_attribute.color_format, pixel_channel::alpha));
        glfwWindowHint(GLFW_DEPTH_BITS, channel_bits_of_format(render_target_attribute.depth_format, pixel_channel::depth));
        glfwWindowHint(GLFW_STENCIL_BITS, channel_bits_of_format(render_target_attribute.depth_format, pixel_channel::stencil));
        glfwWindowHint(GLFW_SAMPLES, render_target_attribute.sample_count > 1 ? render_target_attribute.sample_count : 0);
        #if SAM_DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        #endif
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfw_window_ptr = glfwCreateWindow(render_target_attribute.width, render_target_attribute.height, render_target_attribute.title.c_str(), nullptr, nullptr);
        s_assert(available());
        glfwMakeContextCurrent(glfw_window_ptr);
        // glfwSwapInterval(swap_interval);
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        s_check_gl_error();
    }

    void glfw_window::finalize()
    {
        s_assert(available());
        glfwDestroyWindow(glfw_window_ptr);
        glfw_window_ptr = nullptr;
        glfwTerminate();
        window_base::finalize();
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