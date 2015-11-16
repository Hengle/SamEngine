#pragma once

#include <ResourceModule.h>

#include <glm.hpp>

namespace SamEngine
{
    class Texture;

    typedef std::shared_ptr<Texture> TexturePtr;

    class ASSET_API Texture
    {
    public:
        CREATE_FUNC_DECLARE(Texture)

        explicit Texture(const std::string &location, bool antiAlias = true, DataPtr data = nullptr);

        Texture(TexturePtr texture, float32 regionX, float32 regionY, float32 regionWidth, float32 regionHeight,
            bool rotate = false, float32 offsetX = 0.0f, float32 offsetY = 0.0f, float32 frameWidth = 0.0f, float32 frameHeight = 0.0f);

        virtual ~Texture();

        bool Available();

        const ResourceID &GetResourceID() const;

        bool IsAntiAlias() const;

        bool IsPreMultipliedAlpha() const;

        int32 GetMipmapCount() const;

        int32 GetPixelWidth() const;

        int32 GetPixelHeight() const;

        float32 GetWidth() const;

        float32 GetHeight() const;

        float32 GetOffsetX() const;

        float32 GetOffsetY() const;

        float32 GetFrameWidth() const;

        float32 GetFrameHeight() const;

        glm::vec2 TransformUV(glm::vec2 uv);

    private:
        // base texture
        std::string mName;
        ResourceID mResourceID{ InvalidResourceID };
        bool mAntiAlias{ true };
        bool mPreMultipliedAlpha{ false };
        int32 mMipmapCount{ 1 };
        int32 mPixelWidth{ 0 };
        int32 mPixelHeight{ 0 };
        float32 mWidth{ 0.0f };
        float32 mHeight{ 0.0f };
        // sub texture
        TexturePtr mBase{ nullptr };
        float32 mOffsetX{ 0.0f };
        float32 mOffsetY{ 0.0f };
        float32 mFrameWidth{ 0.0f };
        float32 mFrameHeight{ 0.0f };
        glm::mat4 mUVMatrix;
        // cache function
        std::function<void()> mCacheFunction{ nullptr };
    };

    inline bool Texture::Available()
    {
        if (mBase && mCacheFunction && mBase->Available())
        {
            mCacheFunction();
            mCacheFunction = nullptr;
        }
        return mBase ? mBase->Available() : mResourceID != InvalidResourceID;
    }

    inline const ResourceID &Texture::GetResourceID() const
    {
        return mBase ? mBase->GetResourceID() : mResourceID;
    }

    inline bool Texture::IsAntiAlias() const
    {
        return mBase ? mBase->IsAntiAlias() : mAntiAlias;
    }

    inline bool Texture::IsPreMultipliedAlpha() const
    {
        return mBase ? mBase->IsPreMultipliedAlpha() : mPreMultipliedAlpha;
    }

    inline int32 Texture::GetMipmapCount() const
    {
        return mBase ? mBase->GetMipmapCount() : mMipmapCount;
    }

    inline int32 Texture::GetPixelWidth() const
    {
        return mBase ? mBase->GetPixelWidth() : mPixelWidth;
    }

    inline int32 Texture::GetPixelHeight() const
    {
        return mBase ? mBase->GetPixelHeight() : mPixelHeight;
    }

    inline float32 Texture::GetWidth() const
    {
        return mWidth;
    }

    inline float32 Texture::GetHeight() const
    {
        return mHeight;
    }

    inline float32 Texture::GetOffsetX() const
    {
        return mOffsetX;
    }

    inline float32 Texture::GetOffsetY() const
    {
        return mOffsetY;
    }

    inline float32 Texture::GetFrameWidth() const
    {
        return mFrameWidth;
    }

    inline float32 Texture::GetFrameHeight() const
    {
        return mFrameHeight;
    }

    inline glm::vec2 Texture::TransformUV(glm::vec2 uv)
    {
        auto vector = mUVMatrix * glm::vec4(uv, 1.0f, 1.0f);
        return{ vector.x, vector.y };
    }
}