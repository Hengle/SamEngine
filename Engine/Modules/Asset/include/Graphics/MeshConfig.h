#pragma once

#include "AssetDefine.h"

#include <GraphicsModule.h>

namespace SamEngine
{
    struct ASSET_API DrawCallConfig
    {
        DrawType Type{ DrawType::TRIANGLES };

        int32 First{ 0 };

        int32 Count{ 0 };
    };

    class ASSET_API MeshConfig
    {
    public:
        explicit MeshConfig(uint32 vertexCount, uint32 indexCount = 0, IndexAttributeType type = IndexAttributeType::NONE, BufferUsage vertexUsage = BufferUsage::IMMUTABLE, BufferUsage indexUsage = BufferUsage::IMMUTABLE);

        VertexLayout &VertexLayout();

        MeshConfig &BeginVertex();

        MeshConfig &EndVertex();

        MeshConfig &Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x);

        MeshConfig &Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x, float32 y);

        MeshConfig &Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x, float32 y, float32 z);

        MeshConfig &Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x, float32 y, float32 z, float32 w);

        MeshConfig &BeginIndex();

        MeshConfig &EndIndex();

        MeshConfig &IndexUint16(uint16 vertexIndex);

        MeshConfig &IndexUint32(uint32 vertexIndex);

        MeshConfig &IndexTriangle16(uint16 vertexIndex1, uint16 vertexIndex2, uint16 vertexIndex3);

        MeshConfig &IndexTriangle32(uint32 vertexIndex1, uint32 vertexIndex2, uint32 vertexIndex3);

        MeshConfig &IndexQuad16(uint32 vertexIndex1, uint32 vertexIndex2, uint32 vertexIndex3, uint32 vertexIndex4);

        MeshConfig &IndexQuad32(uint32 vertexIndex1, uint32 vertexIndex2, uint32 vertexIndex3, uint32 vertexIndex4);

        MeshConfig &DrawCall(DrawType type, int32 first, int32 count);

        void Clear();

    private:
        VertexBufferConfig mVertexBufferConfig;
        IndexBufferConfig mIndexBufferConfig;
        DrawCallConfig mDrawCallConfig[MaxDrawCallInMesh];
        int32 mDrawCallCount{ 0 };
        DataPtr mVertexData{ nullptr };
        DataPtr mIndexData{ nullptr };
        uchar *mVertexPtr{ nullptr };
        uchar *mIndexPtr{ nullptr };

        friend class Mesh;
    };

    inline VertexLayout &MeshConfig::VertexLayout()
    {
        return mVertexBufferConfig.Layout;
    }

    inline void MeshConfig::Clear()
    {
        mVertexBufferConfig = VertexBufferConfig();
        mIndexBufferConfig = IndexBufferConfig();
        mVertexData->Clear();
        mVertexData.reset();
        mIndexData->Clear();
        mIndexData.reset();
        mVertexPtr = nullptr;
        mIndexPtr = nullptr;
    }
}