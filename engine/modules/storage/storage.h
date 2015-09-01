#pragma once

#include "config/storage_config.h"
#include "filesystem/storage_filesystem.h"

#include <core/data.h>

#include <string>

namespace sam
{
    class storage
    {
    public:
        static void initialize(const storage_config &config);

        static void finalize();

        static bool available();

        static data_ptr read(const std::string &path);

        static void write(const std::string &path, data_ptr data);

    private:
        static class state
        {
        public:
            std::string path;
        } *storage_state;
    };
}