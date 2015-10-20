#pragma once

#include <ResourceModule.h>

#include <functional>

namespace SamEngine
{
    typedef std::function<void(ResourceID)> TextureLoaderCallback;

    class ASSET_API TextureLoader
    {
    public:
        static ResourceID Load(DataPtr data);

        static void Load(const std::string &location, TextureLoaderCallback callback);
    };
}