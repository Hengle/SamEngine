#include <modules/storage/filesystem/storage_filesystem.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "core/app.h"
#include "io/io.h"
#include "storage/storage.h"

using namespace sam;

class Hello : public app
{

public:
    virtual state initialize() override;

    virtual state running() override;

    virtual state finalize() override;

private:
    GLFWwindow* window;
};

app::state Hello::initialize()
{
    glfwInit();

//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr);

    glfwMakeContextCurrent(window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    io::initialize();

    storage::initialize("/Users/xavierjiang/Desktop/");

    io::set_filesystem("storage", storage_filesystem::creator);

    io::load("storage:test.txt", [](io_request_location_event_ptr &e)
    {
        log::debug((const char *)e->get_data()->get_buffer());
    });

    return app::initialize();
}

app::state Hello::running()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
    return glfwWindowShouldClose(window) ? state::finalize : state::running;
}

app::state Hello::finalize()
{
    return app::finalize();
}

SAM_MAIN(Hello)