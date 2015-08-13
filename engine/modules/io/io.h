#pragma once

#include "core/io_thread.h"

#include <vector>

namespace sam
{
    class io
    {
    public:
        class param
        {
        public:
            explicit param(int32 thread_count = 4) : thread_count(thread_count) {}

            int32 thread_count;
        };

        static void initialize(const param &p = param());

        static void finalize();

        static bool available();

    private:
        static class state
        {
        public:
			explicit state(const param &p);

            ~state();

            std::vector<io_thread_ptr> threads;
        } *io_state;
    };
}