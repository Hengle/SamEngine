#include "OpenGLTextureFactory.h"

#include "OpenGL/Renderer/OpenGLRenderer.h"

namespace SamEngine
{
    ResourceStatus OpenGLTextureFactory::Create(OpenGLTexture &resource, DataPtr data)
    {
        s_assert(data != nullptr);

        auto &config = resource.Config;

        resource.Target = GLEnumFromTextureType(config.Type);

        OpenGLRenderer::Get().ResetTexture();

        glGenTextures(1, &resource.TextureID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(resource.Target, resource.TextureID);

        s_assert(resource.TextureID != 0);
        s_assert(config.MipMapCount == 1 || !(IsTextureFilterModeUseMipmap(config.FilterModeMin) || IsTextureFilterModeUseMipmap(config.FilterModeMag)));

        glTexParameteri(resource.Target, GL_TEXTURE_MIN_FILTER, GLEnumFromTextureFilterMode(config.FilterModeMin));
        glTexParameteri(resource.Target, GL_TEXTURE_MAG_FILTER, GLEnumFromTextureFilterMode(config.FilterModeMag));

        s_assert(config.Type != TextureType::TEXTURE_CUBE || (config.WrapModeS == TextureWrapMode::CLAMP_TO_EDGE && config.WrapModeT == TextureWrapMode::CLAMP_TO_EDGE && config.WrapModeR == TextureWrapMode::CLAMP_TO_EDGE));

        glTexParameteri(resource.Target, GL_TEXTURE_WRAP_S, GLEnumFromTextureWrapMode(config.WrapModeS));
        glTexParameteri(resource.Target, GL_TEXTURE_WRAP_T, GLEnumFromTextureWrapMode(config.WrapModeT));
        glTexParameteri(resource.Target, GL_TEXTURE_WRAP_R, GLEnumFromTextureWrapMode(config.WrapModeR));

        auto faceCount = config.Type == TextureType::TEXTURE_CUBE ? GraphicsConfig::CubeTextureFaceCount : 1;
        auto isCompressed = IsCompressedPixelFormat(config.ColorFormat);
        auto internalFormat = GLEnumFromPixelFormatAsInternal(config.ColorFormat);
        auto layout = isCompressed ? 0 : GLEnumFromPixelFormatAsLayout(config.ColorFormat);
        auto format = GLEnumFromPixelFormatAsFormat(config.ColorFormat);

        for (auto faceIndex = 0; faceIndex < faceCount; ++faceIndex)
        {
            auto realTarget = resource.Target;
            if (config.Type == TextureType::TEXTURE_CUBE)
            {
                switch (faceIndex)
                {
                case 0: realTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_X; break;
                case 1: realTarget = GL_TEXTURE_CUBE_MAP_NEGATIVE_X; break;
                case 2: realTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_Y; break;
                case 3: realTarget = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y; break;
                case 4: realTarget = GL_TEXTURE_CUBE_MAP_POSITIVE_Z; break;
                default: realTarget = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; break;
                }
            }
            for (auto mipMapIndex = 0; mipMapIndex < config.MipMapCount; ++mipMapIndex)
            {
                s_assert(config.DataSize[faceIndex][mipMapIndex] > 0);
                auto width = config.Width >> mipMapIndex;
                auto height = config.Height >> mipMapIndex;
                if (width == 0) width = 1;
                if (height == 0) height = 1;
                if (isCompressed)
                {
                    s_assert(config.DataOffset[faceIndex][mipMapIndex] + config.DataSize[faceIndex][mipMapIndex] <= data->GetSize());
                    glCompressedTexImage2D(realTarget, mipMapIndex, internalFormat, width, height, 0, config.DataSize[faceIndex][mipMapIndex], data->GetBuffer(config.DataOffset[faceIndex][mipMapIndex]));
                }
                else
                {
                    s_assert(config.DataOffset[faceIndex][mipMapIndex] + SizeOfPixelFormat(config.ColorFormat) * width * height <= data->GetSize());
                    glTexImage2D(realTarget, mipMapIndex, internalFormat, width, height, 0, format, layout, data->GetBuffer(config.DataOffset[faceIndex][mipMapIndex]));
                }
            }
        }

        return ResourceStatus::COMPLETED;
    }

    void OpenGLTextureFactory::Destroy(OpenGLTexture &resource)
    {
        OpenGLRenderer::Get().ResetTexture();
        if (resource.TextureID != 0)
        {
            glDeleteTextures(1, &resource.TextureID);
        }
        if (resource.FrameBufferID != 0)
        {
            glDeleteFramebuffers(1, &resource.FrameBufferID);
        }
        if (resource.DepthRenderBufferID != 0)
        {
            glDeleteRenderbuffers(1, &resource.DepthRenderBufferID);
        }
    }
}