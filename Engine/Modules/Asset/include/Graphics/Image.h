#pragma once

#include "Blend.h"
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

        TexturePtr GetTexture() const;

        void SetTexture(TexturePtr value);

        BlendMode GetBlendMode() const;

        void SetBlendMode(BlendMode value);

    protected:
        void InitializeVertices();

        void UpdateVertices();

    private:
        Mesh mMesh;
        UniformData mUniformData;
        TexturePtr mTexture{ nullptr };
        BlendMode mBlendMode{ BlendMode::ALPHA };
    };

    typedef std::shared_ptr<Image> ImagePtr;

    inline TexturePtr Image::GetTexture() const
    {
        return mTexture;
    }

    inline void Image::SetTexture(TexturePtr value)
    {
        auto old = mTexture;
        mTexture = value;
        mUniformData.SetUniformData(2, mTexture);
        if (old == nullptr && mTexture != nullptr)
        {
            InitializeVertices();
        }
        else
        {
            UpdateVertices();
        }
    }

    inline BlendMode Image::GetBlendMode() const
    {
        return mBlendMode;
    }

    inline void Image::SetBlendMode(BlendMode value)
    {
        mBlendMode = value;
    }
}