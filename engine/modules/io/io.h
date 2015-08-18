#pragma once

#include "core/io_thread.h"

#include "core/func_group.h"

#include <map>
#include <vector>

namespace sam
{
    class io
    {
    public:
		typedef std::function<size_t(const event_ptr &, size_t)> route_func;

		typedef std::function<void(event_ptr &)> callback_func;

        class param
        {
        public:
            param(int32 thread_count = 4) : thread_count(thread_count) {}

            int32 thread_count;
        };

        static void initialize(const param &p = param());

        static void finalize();

        static bool available();

        static void read(const location &file, callback_func func);

        static void write(const location &file, const data_ptr &data, callback_func func = nullptr);

		static void set_filesystem(const std::string &name, filesystem::creator func = nullptr);

		static filesystem::creator get_filesystem(const std::string &name);

		static void set_router(route_func func);

		static route_func get_router();

    protected:
        static void main_loop();

		static void handle(const event_ptr &e, callback_func func);

    private:
        static class state
        {
        public:
			explicit state(const param &p);

            ~state();

			uint32 current_thread;

			route_func router;

            func_group::id func_id;

			std::map<std::string, filesystem::creator> fs_registry;

			std::vector<io_thread_ptr> threads;

			std::map<event_ptr, callback_func> handling;
        } *io_state;
    };
}
