#pragma once

#include "filesystem/http_filesystem.h"

#include <core/data.h>

#include <string>

namespace sam
{
    class http
    {
    public:
        static void initialize();

        static void finalize();

        static data_ptr read(const std::string &path);

    private:
        static bool available;
    };
}