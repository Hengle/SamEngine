#include "core.h"

#include "assert.h"

namespace sam
{
    thread_local std::shared_ptr<func_group> core::before_frame_func_group = nullptr;
    thread_local std::shared_ptr<func_group> core::after_frame_func_group = nullptr;
    std::thread::id core::main_thread_id;

    void core::initialize()
    {
        s_assert(!available());
        main_thread_id = std::this_thread::get_id();
        before_frame_func_group = func_group::create();
        after_frame_func_group = func_group::create();
    }

    void core::finalize()
    {
        s_assert(available());
        s_assert(before_frame_func_group != nullptr);
        s_assert(after_frame_func_group != nullptr);
        before_frame_func_group.reset();
        after_frame_func_group.reset();
    }

    bool core::available()
    {
        return main_thread_id != std::thread::id();
    }

    void core::enter_thread()
    {
        s_assert(before_frame_func_group == nullptr);
        s_assert(after_frame_func_group == nullptr);
        before_frame_func_group = func_group::create();
        after_frame_func_group = func_group::create();
    }

    void core::leave_thread()
    {
        s_assert(before_frame_func_group != nullptr);
        s_assert(after_frame_func_group != nullptr);
        before_frame_func_group.reset();
        after_frame_func_group.reset();
    }

    bool core::is_main_thread()
    {
        return std::this_thread::get_id() == main_thread_id;
    }
}