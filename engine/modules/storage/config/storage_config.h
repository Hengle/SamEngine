#pragma once

#include <string>

namespace sam
{
    class storage_config
    {
    public:
        storage_config(const char *path) : path(path) {}

        storage_config(const std::string &path) : path(path) {}

        std::string path;
    };
}