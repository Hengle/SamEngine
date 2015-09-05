#include <core/app.h>
#include <graphics/graphics.h>
#include <window/window.h>

using namespace sam;

const char* vs =
"attribute vec4 position;\n"
"attribute vec4 color0;\n"
"varying vec4 color;\n"
"void main() {\n"
"\tcolor = color0;\n"
"\tgl_Position = position;\n"
"}\n";

const char* fs =
"varying vec4 color;\n"
"void main() {\n"
"\tgl_FragColor = color;\n"
"}\n";

class triangle : public app
{
public:
    virtual app::state initialize() override;

    virtual app::state running() override;

    virtual app::state finalize() override;

private:
    resource::id state;
};

app::state triangle::initialize()
{
    window::initialize(window_config());
    graphics::initialize(graphics_config());
    float vertices[] = {
        0.0f,  0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f,
    };
    auto data = data::create();
    data->copy(vertices, sizeof(vertices));
    auto shader = graphics::create_resource(shader_config::from_source(vs, fs));
    auto config = mesh_config::from_data();
    config.vertices.layout.add({ vertex_attribute_type::position, vertex_attribute_format::float3 });
    config.vertices.layout.add({ vertex_attribute_type::color0, vertex_attribute_format::float4 });
    config.vertices.count = 3;
    config.draws[0].type = draw_type::triangles;
    config.draws[0].count = 3;
    config.draw_count = 1;
    auto mesh = graphics::create_resource(config, data);
    state = graphics::create_resource(draw_state_config::from_mesh_and_shader(mesh, shader));
    return app::initialize();
}

app::state triangle::running()
{
    graphics::apply_default_target();
    graphics::apply_draw_state(state);
    graphics::draw();
    graphics::render();
    window::present();
    return window::should_close() ? app::state::finalize : app::state::running;
}

app::state triangle::finalize()
{
    graphics::finalize();
    window::finalize();
    return app::finalize();
}

SAM_MAIN(triangle)