#pragma once

#include <CoreModule.h>
#include <ResourceModule.h>

namespace SamEngine
{
    class GAME2D_API Texture
    {
    public:
        CREATE_FUNC_DECLARE(Texture)

        explicit Texture(DataPtr data);

        ~Texture();

        int32 GetWidth() const;

        int32 GetHeight() const;

        ResourceID GetGraphicsTexture() const;

    protected:
        ResourceID mGraphicsTexture{ InvalidResourceID };
        int32 mWidth{ 0 };
        int32 mHeight{ 0 };
    };

    typedef std::shared_ptr<Texture> TexturePtr;

    inline int32 Texture::GetWidth() const
    {
        return mWidth;
    }

    inline int32 Texture::GetHeight() const
    {
        return mHeight;
    }

    inline ResourceID Texture::GetGraphicsTexture() const
    {
        return mGraphicsTexture;
    }
}