#include "Graphics/Texture.h"

#include "TextureLoader.h"

#include <GraphicsModule.h>

namespace SamEngine
{
    Texture::Texture(const std::string& location)
    {
        TextureLoader::LoadFromLocation(location, [this](ResourceID id)
        {
            s_assert(id != InvalidResourceID);
            mResourceID = id;
            auto config = GetGraphics().GetResourceManager().GetTextureConfig(mResourceID);
            mPremultipliedAlpha = config.ColorFormat == PixelFormat::RGBA8;
            mWidth = mPixelWidth = config.Width;
            mHeight = mPixelHeight = config.Height;
        });
    }

    Texture::Texture(TexturePtr texture, int32 x, int32 y, int32 width, int32 height)
    {
        s_assert(texture != nullptr);
        mBase = texture;
        mPositionX = x;
        mPositionY = y;
        mWidth = width;
        mHeight = height;
    }

    Texture::~Texture()
    {
        if (mBase == nullptr && mResourceID != InvalidResourceID)
        {
            GetGraphics().GetResourceManager().Destroy(mResourceID);
        }
    }
}