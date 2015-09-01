#pragma once

#include <core/types.h>

#include <string>

namespace sam
{
    class texture_config
    {
    public:
        int32 width;

        int32 height;

        std::string location;
    };
}