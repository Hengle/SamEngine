#pragma once

#include "func_group.h"

#include <thread>

#if defined(SAM_OSX)
#   define thread_local __thread
#endif

namespace sam
{
    class core
    {
    public:
        static void initialize();

        static void finalize();

        static bool available();

        static void enter_thread();

        static void leave_thread();

        static bool is_main_thread();

        static const std::unique_ptr<func_group> &get_before_frame_func_group();

        static const std::unique_ptr<func_group> &get_after_frame_func_group();

    private:
        static thread_local class state
        {
        public:
            state();

            ~state();

            std::unique_ptr<func_group> before_frame_func_group;

            std::unique_ptr<func_group> after_frame_func_group;
        } *core_state;
        static std::thread::id main_thread_id;
    };
}