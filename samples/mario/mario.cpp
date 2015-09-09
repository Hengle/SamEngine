#include <core/app.h>
#include <graphics/graphics.h>
#include <window/window.h>
#include <asset/graphics/mesh_generator.h>
#include <asset/graphics/texture_loader.h>
#include <io/io.h>
#include <storage/storage.h>

using namespace sam;

const GLchar* vs =
"#version 150 core\n"
"in vec2 position;"
"in vec2 texcoord0;"
"out vec2 vTexcoord;"
"void main() {"
"   vTexcoord = texcoord0;"
"   gl_Position = vec4(position, 1.0, 1.0);"
"}";
const GLchar* fs =
"#version 150 core\n"
"in vec2 vTexcoord;"
"out vec4 outColor;"
"uniform sampler2D uTexture;"
"void main() {"
"   outColor = texture(uTexture, vTexcoord);"
"}";

class mario : public app
{
public:
    virtual app::state initialize() override;

    virtual app::state running() override;

    virtual app::state finalize() override;

private:
    resource::id state{ resource::invalid_id };
};

app::state mario::initialize()
{
    window::initialize(window_config());
    graphics::initialize(graphics_config());
    storage::initialize(storage_config("F:\\SamEngine\\build"));
    io::initialize();
    io::set_filesystem("storage", storage_filesystem::creator);
    texture_loader::load("storage:mario.png", [&](resource::id id)
    {
        auto &config = graphics::find_config<texture_config>(id);
        log::debug("%d, %d\n", config.attribute.width, config.attribute.height);
        mesh_generator mesh_gen(4, 6, index_type::uint16);
        mesh_gen.layout()
            .add(vertex_attribute_type::position, vertex_attribute_format::float2)
            .add(vertex_attribute_type::texcoord0, vertex_attribute_format::float2);
        mesh_gen.draw_call(draw_type::triangles, 0, 6)
            .start()
            .vertex(0, vertex_attribute_type::position, -0.5f, 0.5f)
            .vertex(0, vertex_attribute_type::texcoord0, 0.0f, 0.0f)
            .vertex(1, vertex_attribute_type::position, 0.5f, 0.5f)
            .vertex(1, vertex_attribute_type::texcoord0, 1.0f, 0.0f)
            .vertex(2, vertex_attribute_type::position, 0.5f, -0.5f)
            .vertex(2, vertex_attribute_type::texcoord0, 1.0f, 1.0f)
            .vertex(3, vertex_attribute_type::position, -0.5f, -0.5f)
            .vertex(3, vertex_attribute_type::texcoord0, 0.0f, 1.0f)
            .index_quad16(0, 1, 2, 3)
            .finish();
        auto mesh = graphics::create_resource(mesh_gen.generate_config(), mesh_gen.generate_data());
        auto shader = graphics::create_resource(shader_config::from_source(vs, fs));
        state = graphics::create_resource(draw_state_config::from_mesh_and_shader(mesh, shader));
    });
    return app::initialize();
}

app::state mario::running()
{
    graphics::apply_default_target();
    graphics::apply_draw_state(state);
    graphics::draw();
    graphics::render();
    window::present();
    return window::should_close() ? app::state::finalize : app::state::running;
}

app::state mario::finalize()
{
    graphics::finalize();
    window::finalize();
    return app::finalize();
}

SAM_MAIN(mario)