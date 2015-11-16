#pragma once

#include <GraphicsModule.h>

namespace SamEngine
{
    class ASSET_API IndexBuilder
    {
    public:
        explicit IndexBuilder(uint32 count, IndexAttributeType type = IndexAttributeType::UINT16, BufferUsage usage = BufferUsage::IMMUTABLE);

        IndexBuilder &Begin();

        IndexBuilder &End();

        IndexBuilder &IndexUint16(int32 offset, uint16 vertexIndex);

        IndexBuilder &IndexUint32(int32 offset, uint32 vertexIndex);

        IndexBuilder &IndexTriangle16(int32 offset, uint16 vertexIndex1, uint16 vertexIndex2, uint16 vertexIndex3);

        IndexBuilder &IndexTriangle32(int32 offset, uint32 vertexIndex1, uint32 vertexIndex2, uint32 vertexIndex3);

        IndexBuilder &IndexQuad16(int32 offset, uint16 vertexIndex1, uint16 vertexIndex2, uint16 vertexIndex3, uint16 vertexIndex4);

        IndexBuilder &IndexQuad32(int32 offset, uint32 vertexIndex1, uint32 vertexIndex2, uint32 vertexIndex3, uint32 vertexIndex4);

        void Clear();

        const IndexBufferConfig &GetConfig() const;

        DataPtr GetData() const;

    private:
        IndexBufferConfig mConfig;
        DataPtr mData{ nullptr };
    };

    inline const IndexBufferConfig &IndexBuilder::GetConfig() const
    {
        return mConfig;
    }

    inline DataPtr IndexBuilder::GetData() const
    {
        return mData;
    }
}