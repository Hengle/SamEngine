#pragma once

#include <ResourceModule.h>

namespace SamEngine
{
    class ASSET_API Texture
    {
    public:
        CREATE_FUNC_DECLARE(Texture)

        explicit Texture(ResourceID id, int32 x = 0, int32 y = 0, int32 width = 0, int32 height = 0);

        bool GetPremultipliedAlpha() const;

        int32 GetPositionX() const;

        void SetPositionX(int32 value);

        int32 GetPositionY() const;

        void SetPositionY(int32 value);

        int32 GetWidth() const;

        void SetWidth(int32 value);

        int32 GetHeight() const;

        void SetHeight(int32 value);

        int32 GetPixelWidth() const;

        int32 GetPixelHeight() const;

        float32 GetNormalizedLeft() const;

        float32 GetNormalizedRight() const;

        float32 GetNormalizedTop() const;

        float32 GetNormalizedBottom() const;

    private:
        ResourceID mID{ InvalidResourceID };
        bool mPremultipliedAlpha{ false };
        int32 mPositionX{ 0 };
        int32 mPositionY{ 0 };
        int32 mWidth{ 0 };
        int32 mHeight{ 0 };
        int32 mPixelWidth{ 0 };
        int32 mPixelHeight{ 0 };

        friend class UniformData;
    };

    typedef std::shared_ptr<Texture> TexturePtr;

    inline bool Texture::GetPremultipliedAlpha() const
    {
        return mPremultipliedAlpha;
    }

    inline int32 Texture::GetPositionX() const
    {
        return mPositionX;
    }

    inline void Texture::SetPositionX(int32 value)
    {
        mPositionX = value;
    }

    inline int32 Texture::GetPositionY() const
    {
        return mPositionY;
    }

    inline void Texture::SetPositionY(int32 value)
    {
        mPositionY = value;
    }

    inline int32 Texture::GetWidth() const
    {
        return mWidth;
    }

    inline void Texture::SetWidth(int32 value)
    {
        mWidth = value;
    }

    inline int32 Texture::GetHeight() const
    {
        return mHeight;
    }

    inline void Texture::SetHeight(int32 value)
    {
        mHeight = value;
    }

    inline int32 Texture::GetPixelWidth() const
    {
        return mPixelWidth;
    }

    inline int32 Texture::GetPixelHeight() const
    {
        return mPixelHeight;
    }

    inline float32 Texture::GetNormalizedLeft() const
    {
        return static_cast<float32>(mPositionX) / static_cast<float32>(mPixelWidth);
    }

    inline float32 Texture::GetNormalizedRight() const
    {
        return static_cast<float32>(mPositionX + mWidth) / static_cast<float32>(mPixelWidth);
    }

    inline float32 Texture::GetNormalizedTop() const
    {
        return static_cast<float32>(mPositionY) / static_cast<float32>(mPixelHeight);
    }

    inline float32 Texture::GetNormalizedBottom() const
    {
        return static_cast<float32>(mPositionY + mHeight) / static_cast<float32>(mPixelHeight);
    }
}