#include "Texture/Texture.h"

#include <AssetModule.h>
#include <GraphicsModule.h>

namespace SamEngine
{
    Texture::Texture(DataPtr data)
    {
        s_assert(data != nullptr);
        mGraphicsTexture = TextureLoader::Load(data);
        if (mGraphicsTexture != InvalidResourceID)
        {
            auto config = GetGraphics().GetResourceManager().GetTextureConfig(mGraphicsTexture);
            mWidth = config.Width;
            mHeight = config.Height;
        }
    }

    Texture::~Texture()
    {
        if (mGraphicsTexture != InvalidResourceID)
        {
            GetGraphics().GetResourceManager().Destroy(mGraphicsTexture);
        }
    }
}