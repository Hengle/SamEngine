#pragma once

#include <ResourceModule.h>

namespace SamEngine
{
    class ASSET_API ImageShader
    {
    public:
        static void Initialize();

        static void Finalize();

        static void Apply();

        static ResourceID GetResourceID();

    private:
        static ResourceID mResourceID;
    };
}