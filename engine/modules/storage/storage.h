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
        static data_ptr read(const std::string &path);

        static void write(const std::string &path, data_ptr data);
    };
}