#include "core/app.h"
#include "io/io.h"
#include "graphics/graphics.h"
#include "storage/storage.h"

#include <sstream>

using namespace sam;

class Hello : public app
{

public:
    virtual state initialize() override;

    virtual state running() override;

    virtual state finalize() override;
};

app::state Hello::initialize()
{
    graphics::initialize(graphics::param::window(800, 600, "Sam"));

    io::initialize();

    storage::initialize("C:\\Users\\leafnsand\\Desktop\\");

    io::set_filesystem("storage", storage_filesystem::creator);

    io::read("storage:test.txt", [](event_ptr &e)
    {
        auto event = std::dynamic_pointer_cast<io_request_read_event>(e);

        log::debug("%s\n", (const char *) event->get_data()->get_buffer());

        io::write("storage:copy.txt", event->get_data());
    });

    return app::initialize();
}

app::state Hello::running()
{
    graphics::present();
    return graphics::should_quit() ? state::finalize : state::running;
}

app::state Hello::finalize()
{
    graphics::finalize();
    storage::finalize();
    io::finalize();
    return app::finalize();
}

SAM_MAIN(Hello)