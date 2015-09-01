#include "core/app.h"
#include "graphics/graphics.h"

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
    graphics::initialize(graphics_config());

    return app::initialize();
}

app::state clear_color::running()
{
    graphics::apply_default_target(state);
    graphics::present();

    state.color += color(0.01, 0.005, 0.0025f, 0.0);
    state.color = glm::mod(state.color, color(1.0f));

    return graphics::should_quit() ? app::state::finalize : app::state::running;
}

app::state clear_color::finalize()
{
    graphics::finalize();
    return app::finalize();
}

SAM_MAIN(clear_color)