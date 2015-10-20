#pragma once

#include <CoreModule.h>

namespace SamEngine
{
    class GAME2D_API Drawable
    {
    public:
        virtual ~Drawable() {}

        virtual void Draw() = 0;

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
    };

    typedef std::shared_ptr<Drawable> DrawablePtr;

    inline bool Drawable::IsVisilble() const
    {
        return mVisible;
    }

    inline void Drawable::SetVisible(bool value)
    {
        mVisible = value;
    }

    inline float32 Drawable::GetPositionX() const
    {
        return mPositionX;
    }

    inline void Drawable::SetPositionX(float32 value)
    {
        mPositionX = value;
    }

    inline float32 Drawable::GetPositionY() const
    {
        return mPositionY;
    }

    inline void Drawable::SetPositionY(float32 value)
    {
        mPositionY = value;
    }

    inline float32 Drawable::GetRotation() const
    {
        return mRotation;
    }

    inline void Drawable::SetRotation(float32 value)
    {
        mRotation = value;
    }

    inline float32 Drawable::GetScaleX() const
    {
        return mScaleX;
    }

    inline void Drawable::SetScaleX(float32 value)
    {
        mScaleX = value;
    }

    inline float32 Drawable::GetScaleY() const
    {
        return mScaleY;
    }

    inline void Drawable::SetScaleY(float32 value)
    {
        mScaleY = value;
    }

    inline float32 Drawable::GetOffsetX() const
    {
        return mOffsetX;
    }

    inline void Drawable::SetOffsetX(float32 value)
    {
        mOffsetX = value;
    }

    inline float32 Drawable::GetOffsetY() const
    {
        return mOffsetY;
    }

    inline void Drawable::SetOffsetY(float32 value)
    {
        mOffsetY = value;
    }

    inline float32 Drawable::GetSkewX() const
    {
        return mSkewX;
    }

    inline void Drawable::SetSkewX(float32 value)
    {
        mSkewX = value;
    }

    inline float32 Drawable::GetSkewY() const
    {
        return mSkewY;
    }

    inline void Drawable::SetSkewY(float32 value)
    {
        mSkewY = value;
    }
}