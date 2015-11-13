#pragma once

#include "Blend.h"
#include "ImageBatcher.h"
#include "Core/Drawable.h"
#include "Core/Texture.h"

namespace SamEngine
{
    class ASSET_API Image : public Drawable
    {
    public:
        CREATE_FUNC_DECLARE(Image)

        explicit Image(TexturePtr texture = nullptr) : mTexture(texture) {}

        virtual ~Image() {}

        void Draw() override;

        TexturePtr GetTexture() const;

        void SetTexture(TexturePtr value);

        BlendMode GetBlendMode() const;

        void SetBlendMode(BlendMode value);

        float32 GetWidth() const;

        void SetWidth(float32 value);

        float32 GetHeight() const;

        void SetHeight(float32 value);

        float32 GetAlpha() const;

        void SetAlpha(float32 value);

        Color GetColor() const;

        void SetColor(Color value);

        uint32 GetIntColor() const;

        void SetIntColor(uint32 value);

    private:
        TexturePtr mTexture{ nullptr };
        BlendMode mBlendMode{ BlendMode::PRE_MULTIPLIED };
        Color mColor{ 1.0f, 1.0f, 1.0f, 1.0f };
    };

    typedef std::shared_ptr<Image> ImagePtr;

    inline TexturePtr Image::GetTexture() const
    {
        return mTexture;
    }

    inline void Image::SetTexture(TexturePtr value)
    {
        mTexture = value;
    }

    inline BlendMode Image::GetBlendMode() const
    {
        return mBlendMode;
    }

    inline void Image::SetBlendMode(BlendMode value)
    {
        mBlendMode = value;
    }

    inline float32 Image::GetWidth() const
    {
        auto value = 0;
        if (mTexture != nullptr)
        {
            value = mTexture->GetWidth() * mScale.x;
        }
        return value;
    }

    inline void Image::SetWidth(float32 value)
    {
        if (mTexture != nullptr)
        {
            mScale.x = value / static_cast<float32>(mTexture->GetWidth());
        }
    }

    inline float32 Image::GetHeight() const
    {
        auto value = 0;
        if (mTexture != nullptr)
        {
            value = mTexture->GetHeight() * mScale.y;
        }
        return value;
    }

    inline void Image::SetHeight(float32 value)
    {
        if (mTexture != nullptr)
        {
            mScale.y = value / static_cast<float32>(mTexture->GetHeight());
        }
    }

    inline float32 Image::GetAlpha() const
    {
        return mColor.a;
    }

    inline void Image::SetAlpha(float32 value)
    {
        mColor.a = value;
    }

    inline Color Image::GetColor() const
    {
        return mColor;
    }

    inline void Image::SetColor(Color value)
    {
        mColor = value;
    }

    inline uint32 Image::GetIntColor() const
    {
        return (static_cast<uint32>(mColor.r * 0xFF) & 0xFF) << 24 |
            (static_cast<uint32>(mColor.g * 0xFF) & 0xFF) << 16 |
            (static_cast<uint32>(mColor.b * 0xFF) & 0xFF) << 8 |
            (static_cast<uint32>(mColor.a * 0xFF) & 0xFF);
    }

    inline void Image::SetIntColor(uint32 value)
    {
        mColor.r = static_cast<float32>(value >> 24 & 0xFF) / 255.0f;
        mColor.g = static_cast<float32>(value >> 16 & 0xFF) / 255.0f;
        mColor.b = static_cast<float32>(value >> 8 & 0xFF) / 255.0f;
        mColor.a = static_cast<float32>(value & 0xFF) / 255.0f;
    }

    inline void Image::Draw()
    {
        if (mVisible && mTexture && mTexture->Available())
        {
            ImageBatcher::AddImage(this);
        }
    }
}