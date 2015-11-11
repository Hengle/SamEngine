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
        CREATE_FUNC_DECLARE(Mesh)

        Mesh(const VertexBuilder &vertex, const IndexBuilder &index);

        virtual ~Mesh();

        void UpdateVertices(const VertexBuilder &vertex);

        void AddDrawCall(DrawType type, int32 first, int32 count);

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

    typedef std::shared_ptr<Mesh> MeshPtr;
}