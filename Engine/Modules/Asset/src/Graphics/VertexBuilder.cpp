#include "Graphics/VertexBuilder.h"

#include "VertexUtil.h"

namespace SamEngine
{
    VertexBuilder::VertexBuilder(uint32 count, BufferUsage usage)
    {
        mConfig.Usage = usage;
        mConfig.Count = count;
    }

    VertexLayout &VertexBuilder::Layout()
    {
        return mConfig.Layout;
    }

    VertexBuilder &VertexBuilder::Begin()
    {
        s_assert(mData == nullptr);
        mData = Data::Create(mConfig.Size());
        return *this;
    }

    VertexBuilder &VertexBuilder::End()
    {
        s_assert(mData != nullptr);
        return *this;
    }

    VertexBuilder &VertexBuilder::Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x)
    {
        s_assert(vertexIndex < mConfig.Count);
        s_assert(mData != nullptr);
        VertexUtil::Write(mData->GetBuffer(vertexIndex * mConfig.Layout.Size() + mConfig.Layout.OffsetOf(attribute)), mConfig.Layout.FormatOf(attribute), x);
        return *this;
    }

    VertexBuilder &VertexBuilder::Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x, float32 y)
    {
        s_assert(vertexIndex < mConfig.Count);
        s_assert(mData != nullptr);
        VertexUtil::Write(mData->GetBuffer(vertexIndex * mConfig.Layout.Size() + mConfig.Layout.OffsetOf(attribute)), mConfig.Layout.FormatOf(attribute), x, y);
        return *this;
    }

    VertexBuilder &VertexBuilder::Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x, float32 y, float32 z)
    {
        s_assert(vertexIndex < mConfig.Count);
        s_assert(mData != nullptr);
        VertexUtil::Write(mData->GetBuffer(vertexIndex * mConfig.Layout.Size() + mConfig.Layout.OffsetOf(attribute)), mConfig.Layout.FormatOf(attribute), x, y, z);
        return *this;
    }

    VertexBuilder &VertexBuilder::Vertex(uint32 vertexIndex, VertexAttributeType attribute, float32 x, float32 y, float32 z, float32 w)
    {
        s_assert(vertexIndex < mConfig.Count);
        s_assert(mData != nullptr);
        VertexUtil::Write(mData->GetBuffer(vertexIndex * mConfig.Layout.Size() + mConfig.Layout.OffsetOf(attribute)), mConfig.Layout.FormatOf(attribute), x, y, z, w);
        return *this;
    }

    void VertexBuilder::Clear()
    {
        mData.reset();
    }
}