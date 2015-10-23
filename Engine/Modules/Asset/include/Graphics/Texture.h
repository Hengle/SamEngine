#pragma once

#include <ResourceModule.h>

namespace SamEngine
{
    class ASSET_API Texture
    {
    public:
        CREATE_FUNC_DECLARE(Texture)

        explicit Texture(ResourceID id);

        Texture(ResourceID id, int32 x, int32 y, int32 width, int32 height);

        int32 GetPositionX() const;

        void SetPositionX(int32 value);

        int32 GetPositionY() const;

        void SetPositionY(int32 value);

        int32 GetWidth() const;

        void SetWidth(int32 value);

        int32 GetHeight() const;

        void SetHeight(int32 value);

    private:
        ResourceID mID{ InvalidResourceID };
        int32 mPositionX{ 0 };
        int32 mPositionY{ 0 };
        int32 mWidth{ 0 };
        int32 mHeight{ 0 };

        friend class UniformData;
    };

    typedef std::shared_ptr<Texture> TexturePtr;

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

}