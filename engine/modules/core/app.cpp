#include "app.h"
#include "assert.h"
#include "core.h"

namespace sam
{
    app *app::instance = nullptr;

    app::app() :
        current(state::initialize),
        next(state::invalid)
    {
        instance = this;
    }

    app::~app()
    {
        instance = nullptr;
    }

    void app::start()
    {
        s_assert(instance != nullptr);
        core::initialize();
        log::info("app start\n");
        while (state::invalid != current)
        {
            main_loop();
        }
        log::info("app quit\n");
        core::finalize();
    }

    void app::quit()
    {
        next = state::finalize;
    }

    void app::main_loop()
    {
        if (next != state::invalid && next != current)
        {
            log::info("[app::main_loop] app state: %d\n", next);
            current = next;
            next = state::invalid;
        }
        core::before_frame_func_group->run();
        switch (current)
        {
            case state::initialize:
                next = initialize();
                break;
            case state::running:
                next = running();
                break;
            case state::finalize:
                next = finalize();
                current = state::invalid;
                break;
            default:
                log::warning("[app::main_loop] unknown app state %d\n", current);
                break;
        }
        core::after_frame_func_group->run();
    }

    app::state app::initialize()
    {
        return state::running;
    }

    app::state app::running()
    {
        return state::finalize;
    }

    app::state app::finalize()
    {
        return state::invalid;
    }
}