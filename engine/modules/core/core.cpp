#include "core.h"

#include "assert.h"

namespace sam
{
    core::state::state()
    {
        before_frame_func_group = std::make_unique<func_group>();
        after_frame_func_group = std::make_unique<func_group>();
    }

    core::state::~state()
    {
        before_frame_func_group.reset();
        after_frame_func_group.reset();
    }

    thread_local core::state *core::core_state = nullptr;
    std::thread::id core::main_thread_id;

    void core::initialize()
    {
        s_assert(!available());
        main_thread_id = std::this_thread::get_id();
		core_state = new state();
    }

    void core::finalize()
    {
        s_assert(available());
        s_assert(core_state != nullptr);
        delete core_state;
    }

    bool core::available()
    {
        return main_thread_id != std::thread::id();
    }

    void core::enter_thread()
    {
        s_assert(core_state == nullptr);
        core_state = new state();
    }

    void core::leave_thread()
    {
        s_assert(core_state != nullptr);
        delete core_state;
    }

    bool core::is_main_thread()
    {
        return std::this_thread::get_id() == main_thread_id;
    }

    const std::unique_ptr<func_group> &core::get_before_frame_func_group()
    {
        return core_state->before_frame_func_group;
    }

    const std::unique_ptr<func_group> &core::get_after_frame_func_group()
    {
        return core_state->after_frame_func_group;
    }
}