#include <core/app.h>
#include <io/io.h>
#include <storage/storage.h>

#include <direct.h>

using namespace sam;

class storage_io : public app
{

public:
    virtual app::state initialize() override;

    virtual app::state running() override;

    virtual app::state finalize() override;

private:
    bool complete{ false };
};

app::state storage_io::initialize()
{
    char current[1024];
    if (nullptr == _getcwd(current, 1024))
    {
        return app::finalize();
    }

    storage::initialize(current);

    io::initialize();
    io::set_filesystem("storage", storage_filesystem::creator);

    auto hello = "Hello World!";
    auto test_data = data::create();
    test_data->copy(hello, strlen(hello) + 1);
    io::write("storage:test.txt", test_data, [&](event_ptr &e)
    {
        if (e->get_status() == event::status::complete)
        {
            log::debug("write complete.\n");
            io::read("storage:test.txt", [&](event_ptr &ee)
            {
                if (ee->get_status() == event::status::complete)
                {
                    auto read_event = std::static_pointer_cast<io_request_read_event>(ee);
                    if (read_event)
                    {
                        auto data = read_event->get_data();
                        log::debug("read complete: %s\n", data->get_buffer());
                        complete = true;
                    }
                }
            });
        }
    });

    return app::initialize();
}

app::state storage_io::running()
{
    return complete ? app::state::finalize : app::state::running;
}

app::state storage_io::finalize()
{
    io::finalize();
    storage::finalize();
    return app::finalize();
}

SAM_MAIN(storage_io)