#pragma once

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

    class GAME2D_API Sprite
    {
    public:
        CREATE_FUNC_DECLARE(Sprite)

        virtual ~Sprite() {}

        virtual void Draw();

        bool Contain(SpritePtr child) const;

        void AddChild(SpritePtr child);

        void AddChildAt(int32 index, SpritePtr child);

        void RemoveChild(SpritePtr child);

        void RemoveChildAt(int32 index);

        bool IsVisilble() const;

        void SetVisible(bool value);

        float32 GetPositionX() const;

        void SetPositionX(float32 value);

        float32 GetPositionY() const;

        void SetPositionY(float32 value);

        float32 GetRotation() const;

        void SetRotation(float32 value);

        float32 GetScaleX() const;

        void SetScaleX(float32 value);

        float32 GetScaleY() const;

        void SetScaleY(float32 value);

        float32 GetOffsetX() const;

        void SetOffsetX(float32 value);

        float32 GetOffsetY() const;

        void SetOffsetY(float32 value);

        float32 GetSkewX() const;

        void SetSkewX(float32 value);

        float32 GetSkewY() const;

        void SetSkewY(float32 value);

    protected:
        bool mVisible{ true };
        float32 mPositionX{ 0.0f };
        float32 mPositionY{ 0.0f };
        float32 mRotation{ 0.0f };
        float32 mScaleX{ 1.0f };
        float32 mScaleY{ 1.0f };
        float32 mOffsetX{ 0.0f };
        float32 mOffsetY{ 0.0f };
        float32 mSkewX{ 0.0f };
        float32 mSkewY{ 0.0f };
        std::vector<SpritePtr> mChildren;
    };

    inline bool Sprite::IsVisilble() const
    {
        return mVisible;
    }

    inline void Sprite::SetVisible(bool value)
    {
        mVisible = value;
    }

    inline float32 Sprite::GetPositionX() const
    {
        return mPositionX;
    }

    inline void Sprite::SetPositionX(float32 value)
    {
        mPositionX = value;
    }

    inline float32 Sprite::GetPositionY() const
    {
        return mPositionY;
    }

    inline void Sprite::SetPositionY(float32 value)
    {
        mPositionY = value;
    }

    inline float32 Sprite::GetRotation() const
    {
        return mRotation;
    }

    inline void Sprite::SetRotation(float32 value)
    {
        mRotation = value;
    }

    inline float32 Sprite::GetScaleX() const
    {
        return mScaleX;
    }

    inline void Sprite::SetScaleX(float32 value)
    {
        mScaleX = value;
    }

    inline float32 Sprite::GetScaleY() const
    {
        return mScaleY;
    }

    inline void Sprite::SetScaleY(float32 value)
    {
        mScaleY = value;
    }

    inline float32 Sprite::GetOffsetX() const
    {
        return mOffsetX;
    }

    inline void Sprite::SetOffsetX(float32 value)
    {
        mOffsetX = value;
    }

    inline float32 Sprite::GetOffsetY() const
    {
        return mOffsetY;
    }

    inline void Sprite::SetOffsetY(float32 value)
    {
        mOffsetY = value;
    }

    inline float32 Sprite::GetSkewX() const
    {
        return mSkewX;
    }

    inline void Sprite::SetSkewX(float32 value)
    {
        mSkewX = value;
    }

    inline float32 Sprite::GetSkewY() const
    {
        return mSkewY;
    }

    inline void Sprite::SetSkewY(float32 value)
    {
        mSkewY = value;
    }
}