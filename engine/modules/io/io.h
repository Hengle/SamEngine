#pragma once

#include "core/io_thread.h"

#include "core/func_group.h"

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

        static io_request_url_event_ptr load(const url &file);

        static void dispatch(const io_request_url_event_ptr &e);

		static void set_filesystem(const std::string &name, filesystem_creator func = nullptr);

		static filesystem_creator get_filesystem(const std::string &name);

    private:
        static void main_loop();

    private:
        static class state
        {
        public:
			explicit state(const param &p);

            ~state();

			uint32 current_thread;

            func_group::id func_group_id;

            std::vector<io_thread_ptr> threads;

			std::map<std::string, filesystem_creator> fs_registry;
        } *io_state;
    };
}
