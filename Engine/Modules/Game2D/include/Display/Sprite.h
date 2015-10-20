#pragma once

#include "Drawable.h"

#include <CoreModule.h>

#include <vector>
#include <memory>
#include <functional>

#define ROOT_CREATOR_FUNC_DECLEARE(clazz) \
    static SpritePtr AsRoot() \
    { \
        return std::static_pointer_cast<Sprite>(std::make_shared<clazz>()); \
    }

namespace SamEngine
{
    class Sprite;

    typedef std::shared_ptr<Sprite> SpritePtr;

    typedef std::function<SpritePtr()> RootCreator;

    class GAME2D_API Sprite : public Drawable
    {
    public:
        CREATE_FUNC_DECLARE(Sprite)

        void Draw() override;

        bool Contain(DrawablePtr child) const;

        void AddChild(DrawablePtr child);

        void AddChildAt(int32 index, DrawablePtr child);

        void RemoveChild(DrawablePtr child);

        void RemoveChildAt(int32 index);

    protected:
        std::vector<DrawablePtr> mChildren;
    };
}