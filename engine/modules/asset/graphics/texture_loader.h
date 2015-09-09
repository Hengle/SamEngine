#pragma once

#include <resource/resource.h>

#include <functional>

namespace sam
{
    typedef std::function<void(resource::id)> texture_loader_callback;

    class texture_loader
    {
    public:
        static void load(const std::string &location, texture_loader_callback callback);
    };
}