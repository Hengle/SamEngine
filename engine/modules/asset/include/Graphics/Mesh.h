#pragma once

#include "AssetDefine.h"
#include "MeshConfig.h"

#include <ResourceModule.h>

namespace SamEngine
{
    class ASSET_API Mesh
    {
    public:
        void Create(const MeshConfig &config);

        void Destroy();

        void Draw();

    private:
        ResourceID mVertexBuffer{ InvalidResourceID };
        ResourceID mIndexBuffer{ InvalidResourceID };
        ResourceID mDrawCall[MaxDrawCallInMesh];
        int32 mDrawCallCount{ 0 };
    };
}