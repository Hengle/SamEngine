#include "Display/Sprite.h"

namespace SamEngine
{
    void Sprite::Draw()
    {
        if (mVisible)
        {
            for (auto &child : mChildren)
            {
                child->Draw();
            }
        }
    }

    bool Sprite::Contain(SpritePtr child) const
    {
        return std::find(mChildren.begin(), mChildren.end(), child) != mChildren.end();
    }

    void Sprite::AddChild(SpritePtr child)
    {
        s_assert(!Contain(child));
        mChildren.push_back(child);
    }

    void Sprite::AddChildAt(int32 index, SpritePtr child)
    {
        s_assert(!Contain(child));
        s_assert_range(index, 0, mChildren.size());
        mChildren.insert(mChildren.begin() + index, child);
    }

    void Sprite::RemoveChild(SpritePtr child)
    {
        auto iterator = std::find(mChildren.begin(), mChildren.end(), child);
        s_assert(iterator != mChildren.end());
        mChildren.erase(iterator);
    }

    void Sprite::RemoveChildAt(int32 index)
    {
        s_assert_range(index, 0, mChildren.size() - 1);
        mChildren.erase(mChildren.begin() + index);
    }
}