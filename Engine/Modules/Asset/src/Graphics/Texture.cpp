#include "Graphics/Texture.h"

#include <GraphicsModule.h>

namespace SamEngine
{
    Texture::Texture(ResourceID id, int32 x, int32 y, int32 width, int32 height) :
        mID(id),
        mPositionX(x),
        mPositionY(y),
        mWidth(width),
        mHeight(height)
    {
        s_assert(mID != InvalidResourceID);
        auto config = GetGraphics().GetResourceManager().GetTextureConfig(id);
        mPixelWidth = config.Width;
        mPixelHeight = config.Height;
        if (mWidth == 0)
        {
            mWidth = mPixelWidth;
        }
        if (mHeight == 0)
        {
            mHeight = mPixelHeight;
        }
        s_assert_range(mPositionX, 0, config.Width);
        s_assert_range(mPositionY, 0, config.Height);
        s_assert_range(mPositionX + mWidth, 0, config.Width);
        s_assert_range(mPositionY + mHeight, 0, config.Height);
    }
}