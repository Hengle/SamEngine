#pragma once

#include "AssetDefine.h"
#include "VertexBuilder.h"
#include "IndexBuilder.h"

#include <GraphicsModule.h>

namespace SamEngine
{
    class ASSET_API Mesh
    {
    public:
        ~Mesh();

        void Create(const VertexBuilder &vertex, const IndexBuilder &index);

        void UpdateVertices(const VertexBuilder &vertex);

        void AddDrawCall(DrawType type, int32 first, int32 count);

        void Destroy();

        void Draw();

    private:
        ResourceID mVertexBuffer{ InvalidResourceID };
        ResourceID mIndexBuffer{ InvalidResourceID };
        struct
        {
            DrawType Type;
            int32 First;
            int32 Count;
        } mDrawCall[MaxDrawCallInMesh];
        int32 mDrawCallCount{ 0 };
    };
}