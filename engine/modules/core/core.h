#pragma once

#include "func_group.h"
#include "types.h"

#include <thread>

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

        static thread_local func_group *before_frame_func_group;
        static thread_local func_group *after_frame_func_group;

    private:
        static std::thread::id main_thread_id;
    };
}