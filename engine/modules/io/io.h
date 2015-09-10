#pragma once

#include "core/io_thread.h"
#include "config/io_config.h"

#include <core/func_group.h>

#include <unordered_map>
#include <vector>

namespace sam
{
    class io
    {
    public:
        typedef std::function<size_t(const event_ptr &, size_t)> route_func;

        typedef std::function<void(event_ptr &)> callback_func;

        static void initialize(const io_config &config = io_config());

        static void finalize();

        static bool available();

        static void read(const std::string &file, callback_func func);

        static void write(const std::string &file, const data_ptr &data, callback_func func = nullptr);

        static void set_location_replacement(const std::string &original, const std::string replacement);

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
            explicit state(const io_config &config);

            ~state();

            bool valid{ false };

            uint32 current_thread{ 0 };

            route_func router{ nullptr };

            func_group::id func_id{ func_group::invalid_id };

            std::unordered_map<std::string, std::string> loacation_replacement;

            std::unordered_map<std::string, filesystem::creator> fs_registry;

            std::vector<io_thread_ptr> threads;

            std::vector<event_ptr> handling;

            std::unordered_map<event_ptr, callback_func> event2callback;
        } *io_state;
    };
}
