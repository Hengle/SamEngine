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

        void UpdateVertices(const MeshConfig &config);

        void Destroy();

        void Draw();

    private:
        ResourceID mVertexBuffer{ InvalidResourceID };
        ResourceID mIndexBuffer{ InvalidResourceID };
        DrawCallConfig mDrawCall[MaxDrawCallInMesh];
        int32 mDrawCallCount{ 0 };
    };
}