#pragma once

#include "GraphicsDefine.h"

namespace SamEngine
{
    struct GRAPHICS_API VertexLayoutNode
    {
        VertexLayoutNode();

        VertexLayoutNode(VertexAttributeType attribute, VertexAttributeFormat format);

        int32 Size() const;

        bool operator!=(const VertexLayoutNode &other) const;

        union
        {
            #pragma pack(push, 1)
            struct
            {
                VertexAttributeType Attribute : 8;
                VertexAttributeFormat Format : 8;
            };
            #pragma pack(pop)
            uint16 Value;
        };
    };

    inline VertexLayoutNode::VertexLayoutNode() :
        Attribute(VertexAttributeType::POSITION),
        Format(VertexAttributeFormat::FLOAT1)
    {
    }

    inline VertexLayoutNode::VertexLayoutNode(VertexAttributeType attribute, VertexAttributeFormat format) :
        Attribute(attribute),
        Format(format)
    {
        static_assert(sizeof(VertexLayoutNode) == sizeof(uint16), "wrong size of VertexLayoutNode");
    }

    inline int32 VertexLayoutNode::Size() const
    {
        return SizeOfVertexAttributeFormat(Format);
    }

    inline bool VertexLayoutNode::operator!=(const VertexLayoutNode &other) const
    {
        return Value != other.Value;
    }

    class GRAPHICS_API VertexLayout
    {
    public:
        VertexLayout &Add(VertexAttributeType attribute, VertexAttributeFormat format);

        VertexLayout &Add(const VertexLayoutNode &node);

        VertexLayoutNode &At(int32 index);

        VertexAttributeFormat FormatOf(VertexAttributeType attribute) const;

        bool Empty() const;

        bool Contain(VertexAttributeType attribute) const;

        int32 OffsetOf(VertexAttributeType attribute) const;

        int32 Size() const;

        int32 Length() const;

    private:
        VertexLayoutNode mNodes[GraphicsConfig::MaxVertexNodeCount];
        int32 mCount{ 0 };
    };

    inline VertexLayout &VertexLayout::Add(VertexAttributeType attribute, VertexAttributeFormat format)
    {
        return Add({ attribute, format });
    }

    inline VertexLayout &VertexLayout::Add(const VertexLayoutNode &node)
    {
        s_assert(mCount + 1 < GraphicsConfig::MaxVertexNodeCount);
        s_assert(!Contain(node.Attribute));
        mNodes[mCount++] = node;
        return *this;
    }

    inline VertexLayoutNode &VertexLayout::At(int32 index)
    {
        s_assert_range(index, 0, mCount - 1);
        return mNodes[index];
    }

    inline VertexAttributeFormat VertexLayout::FormatOf(VertexAttributeType attribute) const
    {
        s_assert(Contain(attribute));
        for (auto i = 0; i < mCount; ++i)
        {
            if (mNodes[i].Attribute == attribute)
            {
                return mNodes[i].Format;
            }
        }
        return VertexAttributeFormat::FLOAT1;
    }

    inline bool VertexLayout::Empty() const
    {
        return mCount == 0;
    }

    inline int32 VertexLayout::OffsetOf(VertexAttributeType attribute) const
    {
        auto offset = 0;
        for (auto i = 0; i < mCount; ++i)
        {
            if (mNodes[i].Attribute == attribute)
            {
                break;
            }
            offset += mNodes[i].Size();
        }
        return offset;
    }

    inline bool VertexLayout::Contain(VertexAttributeType attribute) const
    {
        for (auto i = 0; i < mCount; ++i)
        {
            if (mNodes[i].Attribute == attribute)
            {
                return true;
            }
        }
        return false;
    }

    inline int32 VertexLayout::Size() const
    {
        auto total = 0;
        for (auto i = 0; i < mCount; ++i)
        {
            total += mNodes[i].Size();
        }
        return total;
    }

    inline int32 VertexLayout::Length() const
    {
        return mCount;
    }

    struct GRAPHICS_API VertexBufferConfig
    {
        ResourceName Name{ ResourceName::Unique() };

        int32 Count{ 0 };

        VertexLayout Layout;

        BufferUsage Usage{ BufferUsage::IMMUTABLE };

        int32 Size() const;
    };

    inline int32 VertexBufferConfig::Size() const
    {
        return Count * Layout.Size();
    }
}