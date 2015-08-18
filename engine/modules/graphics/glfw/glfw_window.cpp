#include "glfw_window.h"

#include "core/assert.h"

namespace sam
{
    glfw_window::glfw_window(int32 width, int32 height, const std::string &title) :
        window_base(width, height, title),
        glfw_window_ptr(nullptr)
    {
    }

    glfw_window::~glfw_window()
    {
        if (glfw_window::available())
        {
            glfw_window::close();
        }
    }

    void glfw_window::open()
    {
        s_assert(!available());
        if (glfwInit() != GL_TRUE)
        {
            s_error("glfw init error!\n");
        }
        glfwSetErrorCallback(error_callback);
        #if DEBUG
        glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
        #endif
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfw_window_ptr = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        s_assert(available());
        glfwMakeContextCurrent(glfw_window_ptr);
        // glfwSwapInterval(swap_interval);
        gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        s_check_gl_error();
    }

    void glfw_window::close()
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