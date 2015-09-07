#include <core/app.h>
#include <graphics/graphics.h>
#include <window/window.h>
#include <asset/graphics/mesh_generator.h>

using namespace sam;

const GLchar* vs =
"#version 150 core\n"
"in vec2 position;"
"in vec4 color;"
"out vec4 Color;"
"void main() {"
"   Color = color;"
"   gl_Position = vec4(position, 1.0, 1.0);"
"}";
const GLchar* fs =
"#version 150 core\n"
"in vec4 Color;"
"out vec4 outColor;"
"void main() {"
"   outColor = Color;"
"}";

class quad : public app
{
public:
    virtual app::state initialize() override;

    virtual app::state running() override;

    virtual app::state finalize() override;

private:
    resource::id state;
};

app::state quad::initialize()
{
    window::initialize(window_config());
    graphics::initialize(graphics_config());
    mesh_generator mesh_gen(4, 6, index_type::uint16);
    mesh_gen.layout()
        .add(vertex_attribute_type::position, vertex_attribute_format::float2)
        .add(vertex_attribute_type::color0, vertex_attribute_format::float4);
    mesh_gen.draw_call(draw_type::triangles, 0, 6)
        .start()
        .vertex(0, vertex_attribute_type::position, -0.5f, 0.5f)
        .vertex(0, vertex_attribute_type::color0, 1.0f, 0.0f, 0.0f, 1.0f)
        .vertex(1, vertex_attribute_type::position, 0.5f, 0.5f)
        .vertex(1, vertex_attribute_type::color0, 0.0f, 1.0f, 0.0f, 1.0f)
        .vertex(2, vertex_attribute_type::position, 0.5f, -0.5f)
        .vertex(2, vertex_attribute_type::color0, 0.0f, 0.0f, 1.0f, 1.0f)
        .vertex(3, vertex_attribute_type::position, -0.5f, -0.5f)
        .vertex(3, vertex_attribute_type::color0, 1.0f, 1.0f, 1.0f, 1.0f)
        .index_quad16(0, 1, 2, 3)
        .finish();
    auto mesh = graphics::create_resource(mesh_gen.generate_config(), mesh_gen.generate_data());
    auto shader = graphics::create_resource(shader_config::from_source(vs, fs));
    state = graphics::create_resource(draw_state_config::from_mesh_and_shader(mesh, shader));
    return app::initialize();
}

app::state quad::running()
{
    graphics::apply_default_target();
    graphics::apply_draw_state(state);
    graphics::draw();
    graphics::render();
    window::present();
    return window::should_close() ? app::state::finalize : app::state::running;
}

app::state quad::finalize()
{
    graphics::finalize();
    window::finalize();
    return app::finalize();
}

SAM_MAIN(quad)