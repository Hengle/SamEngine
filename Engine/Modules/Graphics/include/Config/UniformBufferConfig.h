#pragma once

#include <GraphicsDefine.h>

#include <string>

namespace SamEngine
{
    class GRAPHICS_API UniformLayoutNode
    {
    public:
        UniformLayoutNode() {}

        UniformLayoutNode(const std::string &name, UniformAttributeFormat type);

        int32 Size() const;

        bool operator!=(const UniformLayoutNode &other) const;

        const std::string &GetName() const;

        UniformAttributeFormat GetType() const;

    private:
        std::string mName;
        UniformAttributeFormat mType{ UniformAttributeFormat::INT };
    };

    inline UniformLayoutNode::UniformLayoutNode(const std::string &name, UniformAttributeFormat type) :
        mName(name),
        mType(type)
    {
    }

    inline int32 UniformLayoutNode::Size() const
    {
        return SizeOfUniformAttributeFormat(mType);
    }

    inline bool UniformLayoutNode::operator!=(const UniformLayoutNode &other) const
    {
        return mType != other.mType || mName != other.mName;
    }

    inline const std::string &UniformLayoutNode::GetName() const
    {
        return mName;
    }

    inline UniformAttributeFormat UniformLayoutNode::GetType() const
    {
        return mType;
    }

    class GRAPHICS_API UniformLayout
    {
    public:
        UniformLayout() {}

        UniformLayout &Add(const std::string &name, UniformAttributeFormat type);

        UniformLayout &Add(const UniformLayoutNode &node);

        UniformLayoutNode &At(int32 index);

        bool Empty() const;

        bool Contain(const std::string &name) const;

        int32 Size() const;

        int32 Length() const;

    private:
        int32 mCount{ 0 };
        UniformLayoutNode mNodes[GraphicsConfig::MaxUniformNodeCount];
    };

    inline UniformLayout &UniformLayout::Add(const std::string &name, UniformAttributeFormat type)
    {
        return Add({ name, type });
    }

    inline UniformLayout &UniformLayout::Add(const UniformLayoutNode &node)
    {
        s_assert(mCount + 1 < GraphicsConfig::MaxUniformNodeCount);
        s_assert(!Contain(node.GetName()));
        mNodes[mCount++] = node;
        return *this;
    }

    inline UniformLayoutNode &UniformLayout::At(int32 index)
    {
        s_assert_range(index, 0, mCount - 1);
        return mNodes[index];
    }

    inline bool UniformLayout::Empty() const
    {
        return mCount == 0;
    }

    inline bool UniformLayout::Contain(const std::string &name) const
    {
        for (auto i = 0; i < mCount; ++i)
        {
            if (mNodes[i].GetName() == name)
            {
                return true;
            }
        }
        return false;
    }

    inline int32 UniformLayout::Size() const
    {
        auto size = 0;
        for (auto i = 0; i < mCount; ++i)
        {
            size += mNodes[i].Size();
        }
        return size;
    }

    inline int32 UniformLayout::Length() const
    {
        return mCount;
    }

    struct GRAPHICS_API UniformBufferConfig
    {
        ResourceName Name{ ResourceName::Unique() };

        ResourceID Program{ InvalidResourceID };

        UniformLayout Layout;

        int32 Size() const;
    };

    inline int32 UniformBufferConfig::Size() const
    {
        return Layout.Size();
    }
}