#pragma once

#include "Drawable.h"
#include "Texture.h"
#include "Mesh.h"
#include "UniformData.h"

namespace SamEngine
{
    class ASSET_API Image : public Drawable
    {
    public:
        CREATE_FUNC_DECLARE(Image)

        explicit Image(TexturePtr texture = nullptr);

        void Draw() override;

        float32 GetWidth() const;

        void SetWidth(float32 value);

        float32 GetHeight() const;

        void SetHeight(float32 value);

        TexturePtr GetTexture() const;

        void SetTexture(TexturePtr value);

    protected:
        void UpdateVertices();

    private:
        Mesh mMesh;
        UniformData mUniformData;
        TexturePtr mTexture{ nullptr };
        float32 mWidth{ 0.0f };
        float32 mHeight{ 0.0f };
    };

    typedef std::shared_ptr<Image> ImagePtr;

    inline float32 Image::GetWidth() const
    {
        return mWidth;
    }

    inline void Image::SetWidth(float32 value)
    {
        mWidth = value;
        UpdateVertices();
    }

    inline float32 Image::GetHeight() const
    {
        return mHeight;
    }

    inline void Image::SetHeight(float32 value)
    {
        mHeight = value;
        UpdateVertices();
    }

    inline TexturePtr Image::GetTexture() const
    {
        return mTexture;
    }

    inline void Image::SetTexture(TexturePtr value)
    {
        mTexture = value;
        mUniformData.SetUniformData(2, mTexture);
        UpdateVertices();
    }
}