#pragma once

#include "Blend.h"
#include "Graphics/Shader.h"
#include "Graphics/VertexBuilder.h"

#include <GraphicsModule.h>

#include <limits>

namespace SamEngine
{
    class Image;

    class ASSET_API ImageBatcher
    {
    public:
        static void Initialize();

        static void Finalize();

        static void AddImage(Image *image);

        static void Flush();
        
    private:
        static struct State
        {
            State() {}
            int32 mImageCount{ 0 };
            BlendMode mBlendMode{ BlendMode::PRE_MULTIPLIED };
            TexturePtr mTexture{ nullptr };
            ResourceID mVertexBuffer{ InvalidResourceID };
            ResourceID mIndexBuffer{ InvalidResourceID };
            VertexBuilder mVertexBuilder{ 4 * std::numeric_limits<uint16>::max() / 6, BufferUsage::DYNAMIC };
        } *mState;
    };
}