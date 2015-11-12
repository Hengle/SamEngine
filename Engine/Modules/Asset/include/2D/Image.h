#pragma once

#include "Blend.h"
#include "DefaultShader.h"
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

    private:
        TexturePtr mTexture{ nullptr };
        BlendMode mBlendMode{ BlendMode::PRE_MULTIPLIED };
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

    inline void Image::Draw()
    {
        if (mVisible && mTexture)
        {
            ImageBatcher::AddImage(this);
        }
    }
}