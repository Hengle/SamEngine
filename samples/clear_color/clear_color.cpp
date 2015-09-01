#include <core/app.h>
#include <graphics/graphics.h>
#include <window/window.h>

using namespace sam;

class clear_color : public app
{

public:
    virtual app::state initialize() override;

    virtual app::state running() override;

    virtual app::state finalize() override;

private:
    clear_state state;
};

app::state clear_color::initialize()
{
    window::initialize(window_config());
    graphics::initialize(graphics_config());
    return app::initialize();
}

app::state clear_color::running()
{
    graphics::apply_default_target(state);
    graphics::render();

    state.color += color(0.01, 0.005, 0.0025f, 0.0);
    state.color = glm::mod(state.color, color(1.0f));

    window::present();

    return window::should_close() ? app::state::finalize : app::state::running;
}

app::state clear_color::finalize()
{
    graphics::finalize();
    window::finalize();
    return app::finalize();
}

SAM_MAIN(clear_color)