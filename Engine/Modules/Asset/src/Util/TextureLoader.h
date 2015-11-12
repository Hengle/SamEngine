#pragma once

#include <ResourceModule.h>

#include <functional>

namespace SamEngine
{
    typedef std::function<void(ResourceID)> TextureLoaderCallback;

    class ASSET_API TextureLoader
    {
    public:
        static ResourceID LoadFromData(const std::string &location, DataPtr data);

        static void LoadFromLocation(const std::string &location, TextureLoaderCallback callback);
    };
}