#pragma once

#include "core/io_thread.h"

#include <vector>

namespace sam
{
    class io
    {
    public:
        static void initialize();

        static void finalize();

        static bool available();

    private:
        static class state
        {
        public:
            state();

            ~state();

            std::vector<io_thread_ptr> threads;
        } *io_state;
    };
}