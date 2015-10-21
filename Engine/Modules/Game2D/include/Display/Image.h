#pragma once

#include "Drawable.h"
#include "Texture/Texture.h"

#include <AssetModule.h>

namespace SamEngine
{
    class GAME2D_API Image : public Drawable
    {
    public:
        CREATE_FUNC_DECLARE(Image)

        Image() {}

        explicit Image(TexturePtr texture);

        void Draw(glm::mat4 matrix) override;

        float32 GetWidth() const;

        void SetWidth(float32 value);

        float32 GetHeight() const;

        void SetHeight(float32 value);

        TexturePtr GetTexture() const;

        void SetTexture(TexturePtr value);

    protected:
        Mesh mMesh;
        UniformData mUniformData;
        TexturePtr mTexture{ nullptr };
        float32 mWidth{ 0.0f };
        float32 mHeight{ 0.0f };
    };

    inline float32 Image::GetWidth() const
    {
        return mWidth;
    }

    inline void Image::SetWidth(float32 value)
    {
        mWidth = value;
    }

    inline float32 Image::GetHeight() const
    {
        return mHeight;
    }

    inline void Image::SetHeight(float32 value)
    {
        mHeight = value;
    }

    inline TexturePtr Image::GetTexture() const
    {
        return mTexture;
    }
}