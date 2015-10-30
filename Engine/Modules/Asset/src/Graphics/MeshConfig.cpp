#include "Graphics/MeshConfig.h"

#include "VertexUtil.h"

namespace SamEngine
{
    MeshConfig::MeshConfig(uint32 vertexCount, uint32 indexCount, IndexAttributeType type, BufferUsage vertexUsage, BufferUsage indexUsage)
    {
        s_assert(type == IndexAttributeType::NONE ||
            type == IndexAttributeType::UINT16 && indexCount > 0 && indexCount <= std::numeric_limits<uint16>::max() ||
            type == IndexAttributeType::UINT32 && indexCount > 0 && indexCount <= std::numeric_limits<uint32>::max());

        mVertexBufferConfig.Usage = vertexUsage;
        mVertexBufferConfig.Count = vertexCount;
        mIndexBufferConfig.Type = type;
        mIndexBufferConfig.Usage = indexUsage;
        mIndexBufferConfig.Count = indexCount;
    }

    MeshConfig &MeshConfig::BeginVertex()
    {
        s_assert(mVertexData == nullptr && mVertexPtr == nullptr);
        mVertexData = Data::Create(mVertexBufferConfig.Size());
        mVertexPtr = mVertexData->GetBuffer();
        return *this;
    }

    MeshConfig &MeshConfig::EndVertex()
    {
        s_assert(mVertexData != nullptr && mVertexPtr == mVertexData->GetBuffer() + mVertexBufferConfig.Size());
        mVertexPtr = nullptr;
        return *this;
    }

    MeshConfig &MeshConfig::Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x)
    {
        mVertexPtr = VertexUtil::Write(mVertexPtr, mVertexBufferConfig.Layout.FormatOf(attribute), x);
        s_assert(mVertexPtr <= mVertexData->GetBuffer() + mVertexBufferConfig.Size());
        return *this;
    }

    MeshConfig &MeshConfig::Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x, float32 y)
    {
        mVertexPtr = VertexUtil::Write(mVertexPtr, mVertexBufferConfig.Layout.FormatOf(attribute), x, y);
        s_assert(mVertexPtr <= mVertexData->GetBuffer() + mVertexBufferConfig.Size());
        return *this;
    }

    MeshConfig &MeshConfig::Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x, float32 y, float32 z)
    {
        mVertexPtr = VertexUtil::Write(mVertexPtr, mVertexBufferConfig.Layout.FormatOf(attribute), x, y, z);
        s_assert(mVertexPtr <= mVertexData->GetBuffer() + mVertexBufferConfig.Size());
        return *this;
    }

    MeshConfig &MeshConfig::Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x, float32 y, float32 z, float32 w)
    {
        mVertexPtr = VertexUtil::Write(mVertexPtr, mVertexBufferConfig.Layout.FormatOf(attribute), x, y, z);
        s_assert(mVertexPtr <= mVertexData->GetBuffer() + mVertexBufferConfig.Size());
        return *this;
    }

    MeshConfig &MeshConfig::BeginIndex()
    {
        s_assert(mVertexData == nullptr && mIndexData == nullptr && mVertexPtr == nullptr && mIndexPtr == nullptr);
        mVertexData = Data::Create(mVertexBufferConfig.Size());
        mVertexPtr = mVertexData->GetBuffer();
        if (mIndexBufferConfig.Type != IndexAttributeType::NONE)
        {
            mIndexData = Data::Create(mIndexBufferConfig.Size());
            mIndexPtr = mIndexData->GetBuffer();
        }
        return *this;
    }

    MeshConfig &MeshConfig::EndIndex()
    {
        if (mIndexBufferConfig.Type != IndexAttributeType::NONE)
        {
            s_assert(mIndexData != nullptr && mIndexPtr == mIndexData->GetBuffer() + mIndexBufferConfig.Size());
        }
        mIndexPtr = nullptr;
        return *this;
    }

    MeshConfig &MeshConfig::IndexUint16(uint16 vertexIndex)
    {
        s_assert(mIndexBufferConfig.Type == IndexAttributeType::UINT16 && vertexIndex < mVertexBufferConfig.Count);
        auto pointer = reinterpret_cast<uint16 *>(mIndexPtr);
        *pointer++ = vertexIndex;
        mIndexPtr = reinterpret_cast<uchar *>(pointer);
        s_assert(mIndexPtr <= mIndexData->GetBuffer() + mIndexData->GetSize());
        return *this;
    }

    MeshConfig &MeshConfig::IndexUint32(uint32 vertexIndex)
    {
        s_assert(mIndexBufferConfig.Type == IndexAttributeType::UINT32 && vertexIndex < mVertexBufferConfig.Count);
        auto pointer = reinterpret_cast<uint32 *>(mIndexPtr);
        *pointer++ = vertexIndex;
        mIndexPtr = reinterpret_cast<uchar *>(pointer);
        s_assert(mIndexPtr <= mIndexData->GetBuffer() + mIndexData->GetSize());
        return *this;
    }

    MeshConfig &MeshConfig::IndexTriangle16(uint16 vertexIndex1, uint16 vertexIndex2, uint16 vertexIndex3)
    {
        s_assert(mIndexBufferConfig.Type == IndexAttributeType::UINT16 &&
            vertexIndex1 < mVertexBufferConfig.Count &&
            vertexIndex2 < mVertexBufferConfig.Count &&
            vertexIndex3 < mVertexBufferConfig.Count);
        auto pointer = reinterpret_cast<uint16 *>(mIndexPtr);
        *pointer++ = vertexIndex1;
        *pointer++ = vertexIndex2;
        *pointer++ = vertexIndex3;
        mIndexPtr = reinterpret_cast<uchar *>(pointer);
        s_assert(mIndexPtr <= mIndexData->GetBuffer() + mIndexData->GetSize());
        return *this;
    }

    MeshConfig &MeshConfig::IndexTriangle32(uint32 vertexIndex1, uint32 vertexIndex2, uint32 vertexIndex3)
    {
        s_assert(mIndexBufferConfig.Type == IndexAttributeType::UINT32 &&
            vertexIndex1 < mVertexBufferConfig.Count &&
            vertexIndex2 < mVertexBufferConfig.Count &&
            vertexIndex3 < mVertexBufferConfig.Count);
        auto pointer = reinterpret_cast<uint32 *>(mIndexPtr);
        *pointer++ = vertexIndex1;
        *pointer++ = vertexIndex2;
        *pointer++ = vertexIndex3;
        mIndexPtr = reinterpret_cast<uchar *>(pointer);
        s_assert(mIndexPtr <= mIndexData->GetBuffer() + mIndexData->GetSize());
        return *this;
    }

    MeshConfig &MeshConfig::IndexQuad16(uint32 vertexIndex1, uint32 vertexIndex2, uint32 vertexIndex3, uint32 vertexIndex4)
    {
        s_assert(mIndexBufferConfig.Type == IndexAttributeType::UINT16 &&
            vertexIndex1 < mVertexBufferConfig.Count &&
            vertexIndex2 < mVertexBufferConfig.Count &&
            vertexIndex3 < mVertexBufferConfig.Count &&
            vertexIndex4 < mVertexBufferConfig.Count);
        auto pointer = reinterpret_cast<uint16 *>(mIndexPtr);
        *pointer++ = vertexIndex1;
        *pointer++ = vertexIndex2;
        *pointer++ = vertexIndex3;
        *pointer++ = vertexIndex1;
        *pointer++ = vertexIndex3;
        *pointer++ = vertexIndex4;
        mIndexPtr = reinterpret_cast<uchar *>(pointer);
        s_assert(mIndexPtr <= mIndexData->GetBuffer() + mIndexData->GetSize());
        return *this;
    }

    MeshConfig &MeshConfig::IndexQuad32(uint32 vertexIndex1, uint32 vertexIndex2, uint32 vertexIndex3, uint32 vertexIndex4)
    {
        s_assert(mIndexBufferConfig.Type == IndexAttributeType::UINT32 &&
            vertexIndex1 < mVertexBufferConfig.Count &&
            vertexIndex2 < mVertexBufferConfig.Count &&
            vertexIndex3 < mVertexBufferConfig.Count &&
            vertexIndex4 < mVertexBufferConfig.Count);
        auto pointer = reinterpret_cast<uint32 *>(mIndexPtr);
        *pointer++ = vertexIndex1;
        *pointer++ = vertexIndex2;
        *pointer++ = vertexIndex3;
        *pointer++ = vertexIndex1;
        *pointer++ = vertexIndex3;
        *pointer++ = vertexIndex4;
        mIndexPtr = reinterpret_cast<uchar *>(pointer);
        s_assert(mIndexPtr <= mIndexData->GetBuffer() + mIndexData->GetSize());
        return *this;
    }

    MeshConfig &MeshConfig::DrawCall(DrawType type, int32 first, int32 count)
    {
        s_assert(mDrawCallCount < MaxDrawCallInMesh);
        mDrawCallConfig[mDrawCallCount].Type = type;
        mDrawCallConfig[mDrawCallCount].First = first;
        mDrawCallConfig[mDrawCallCount].Count = count;
        ++mDrawCallCount;
        return *this;
    }
}