#pragma once

#include <GraphicsModule.h>

namespace SamEngine
{
    class ASSET_API VertexBuilder
    {
    public:
        explicit VertexBuilder(uint32 count, BufferUsage usage = BufferUsage::IMMUTABLE);

        VertexLayout &Layout();

        VertexBuilder &Begin();

        VertexBuilder &End();

        VertexBuilder &Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x);

        VertexBuilder &Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x, float32 y);

        VertexBuilder &Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x, float32 y, float32 z);

        VertexBuilder &Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x, float32 y, float32 z, float32 w);

        void Clear();

        const VertexBufferConfig &GetConfig() const;

        DataPtr GetData() const;

    private:
        VertexBufferConfig mConfig;
        DataPtr mData{ nullptr };
    };

    inline const VertexBufferConfig &VertexBuilder::GetConfig() const
    {
        return mConfig;
    }

    inline DataPtr VertexBuilder::GetData() const
    {
        return mData;
    }
}