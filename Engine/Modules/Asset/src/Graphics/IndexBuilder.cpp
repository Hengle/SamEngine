#include "Graphics/IndexBuilder.h"

namespace SamEngine
{
    IndexBuilder::IndexBuilder(uint32 count, IndexAttributeType type, BufferUsage usage)
    {
        s_assert(type == IndexAttributeType::NONE ||
            type == IndexAttributeType::UINT16 && count > 0 && count <= std::numeric_limits<uint16>::max() ||
            type == IndexAttributeType::UINT32 && count > 0 && count <= std::numeric_limits<uint32>::max());
        mConfig.Count = count;
        mConfig.Type = type;
        mConfig.Usage = usage;
    }

    IndexBuilder &IndexBuilder::Begin()
    {
        s_assert(mData == nullptr);
        mData = Data::Create(mConfig.Size());
        return *this;
    }

    IndexBuilder &IndexBuilder::End()
    {
        s_assert(mData != nullptr);
        return *this;
    }

    IndexBuilder &IndexBuilder::IndexUint16(int32 offset, uint16 vertexIndex)
    {
        s_assert(mConfig.Type == IndexAttributeType::UINT16 && offset < mConfig.Count);
        s_assert(mData != nullptr);
        auto pointer = reinterpret_cast<uint16 *>(mData->GetBuffer(offset * SizeOfIndexAttributeType(mConfig.Type)));
        pointer[0] = vertexIndex;
        return *this;
    }

    IndexBuilder &IndexBuilder::IndexUint32(int32 offset, uint32 vertexIndex)
    {
        s_assert(mConfig.Type == IndexAttributeType::UINT32 && offset < mConfig.Count);
        s_assert(mData != nullptr);
        auto pointer = reinterpret_cast<uint32 *>(mData->GetBuffer(offset * SizeOfIndexAttributeType(mConfig.Type)));
        pointer[0] = vertexIndex;
        return *this;
    }

    IndexBuilder &IndexBuilder::IndexTriangle16(int32 offset, uint16 vertexIndex1, uint16 vertexIndex2, uint16 vertexIndex3)
    {
        s_assert(mConfig.Type == IndexAttributeType::UINT16 && offset + 2 < mConfig.Count);
        s_assert(mData != nullptr);
        auto pointer = reinterpret_cast<uint16 *>(mData->GetBuffer(offset * SizeOfIndexAttributeType(mConfig.Type)));
        pointer[0] = vertexIndex1;
        pointer[1] = vertexIndex2;
        pointer[2] = vertexIndex3;
        return *this;
    }

    IndexBuilder &IndexBuilder::IndexTriangle32(int32 offset, uint32 vertexIndex1, uint32 vertexIndex2, uint32 vertexIndex3)
    {
        s_assert(mConfig.Type == IndexAttributeType::UINT32 && offset + 2 < mConfig.Count);
        s_assert(mData != nullptr);
        auto pointer = reinterpret_cast<uint32 *>(mData->GetBuffer(offset * SizeOfIndexAttributeType(mConfig.Type)));
        pointer[0] = vertexIndex1;
        pointer[1] = vertexIndex2;
        pointer[2] = vertexIndex3;
        return *this;
    }

    IndexBuilder &IndexBuilder::IndexQuad16(int32 offset, uint16 vertexIndex1, uint16 vertexIndex2, uint16 vertexIndex3, uint16 vertexIndex4)
    {
        s_assert(mConfig.Type == IndexAttributeType::UINT16 && offset + 5 < mConfig.Count);
        s_assert(mData != nullptr);
        auto pointer = reinterpret_cast<uint16 *>(mData->GetBuffer(offset * SizeOfIndexAttributeType(mConfig.Type)));
        pointer[0] = vertexIndex1;
        pointer[1] = vertexIndex2;
        pointer[2] = vertexIndex3;
        pointer[3] = vertexIndex1;
        pointer[4] = vertexIndex3;
        pointer[5] = vertexIndex4;
        return *this;
    }

    IndexBuilder &IndexBuilder::IndexQuad32(int32 offset, uint32 vertexIndex1, uint32 vertexIndex2, uint32 vertexIndex3, uint32 vertexIndex4)
    {
        s_assert(mConfig.Type == IndexAttributeType::UINT32 && offset + 5 < mConfig.Count);
        s_assert(mData != nullptr);
        auto pointer = reinterpret_cast<uint32 *>(mData->GetBuffer(offset * SizeOfIndexAttributeType(mConfig.Type)));
        pointer[0] = vertexIndex1;
        pointer[1] = vertexIndex2;
        pointer[2] = vertexIndex3;
        pointer[3] = vertexIndex1;
        pointer[4] = vertexIndex3;
        pointer[5] = vertexIndex4;
        return *this;
    }

    void IndexBuilder::Clear()
    {
        mData.reset();
    }
}