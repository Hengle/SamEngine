#include "Core/Texture.h"
#include "Util/TextureLoader.h"

#include <GraphicsModule.h>

#include <gtc/matrix_transform.hpp>

namespace SamEngine
{
    Texture::Texture(const std::string &location, bool antiAlias, DataPtr data) :
        mName(location),
        mAntiAlias(antiAlias)
    {
        if (data)
        {
            mResourceID = TextureLoader::LoadFromData(location, antiAlias, data);
        }
        else
        {
            mResourceID = TextureLoader::LoadFromLocation(location, antiAlias);
        }
        if (mResourceID == InvalidResourceID)
        {
            GetLog().Error("[Texture] load texture %s fail.\n", mName.c_str());
        }
        else
        {
            auto config = GetGraphics().GetResourceManager().GetTextureConfig(mResourceID);
            mMipmapCount = config.MipMapCount;
            mPreMultipliedAlpha = config.ColorFormat == PixelFormat::RGBA8;
            mWidth = mPixelWidth = config.Width;
            mHeight = mPixelHeight = config.Height;
        }
    }

    Texture::Texture(TexturePtr texture, float32 regionX, float32 regionY, float32 regionWidth, float32 regionHeight,
        bool rotate, float32 offsetX, float32 offsetY, float32 frameWidth, float32 frameHeight) :
        mBase(texture),
        mOffsetX(offsetX),
        mOffsetY(offsetY),
        mFrameWidth(frameWidth),
        mFrameHeight(frameHeight)
    {
        s_assert(mBase != nullptr && mBase->mBase == nullptr);
        s_assert(regionWidth != 0.0f && regionHeight != 0.0f);
        s_assert_range(regionX, 0.0f, mBase->mPixelWidth);
        s_assert_range(regionY, 0.0f, mBase->mPixelHeight);
        s_assert_range(regionX + regionWidth, 0.0f, mBase->mPixelWidth);
        s_assert_range(regionY + regionHeight, 0.0f, mBase->mPixelHeight);
        mWidth = rotate ? regionHeight : regionWidth;
        mHeight = rotate ? regionWidth : regionHeight;
        if (mFrameWidth == 0.0f && mFrameHeight == 0.0f)
        {
            mFrameWidth = mWidth;
            mFrameHeight = mHeight;
        }
        s_assert(mFrameWidth >= mWidth && mFrameHeight >= mHeight);
        mUVMatrix = glm::translate(mUVMatrix, glm::vec3(regionX / mBase->mPixelWidth, regionY / mBase->mPixelHeight, 1.0f));
        mUVMatrix = glm::scale(mUVMatrix, glm::vec3(regionWidth / mBase->mPixelWidth, regionHeight / mBase->mPixelHeight, 1.0f));
        if (rotate)
        {
            mUVMatrix = glm::rotate(mUVMatrix, glm::half_pi<float32>(), glm::vec3(0.0f, 0.0f, 1.0f));
            mUVMatrix = glm::translate(mUVMatrix, glm::vec3(0.0f, -1.0f, 0.0f));
        }
    }

    Texture::~Texture()
    {
        if (mResourceID != InvalidResourceID)
        {
            GetGraphics().GetResourceManager().Destroy(mResourceID);
        }
    }
}