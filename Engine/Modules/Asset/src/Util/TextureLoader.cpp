#include "TextureLoader.h"

#include <GraphicsModule.h>
#include <IOModule.h>

#include <stb_image.h>
#include <gliml.h>

#define RGB_PREMULTIPLY_ALPHA(vr, vg, vb, va) \
    (unsigned)(((unsigned)((unsigned char)(vr) * ((unsigned char)(va) + 1)) >> 8) | \
    ((unsigned)((unsigned char)(vg) * ((unsigned char)(va) + 1) >> 8) << 8) | \
    ((unsigned)((unsigned char)(vb) * ((unsigned char)(va) + 1) >> 8) << 16) | \
    ((unsigned)(unsigned char)(va) << 24))

namespace SamEngine
{
    ResourceID TextureLoader::LoadFromData(const std::string &location, bool antiAlias, DataPtr data)
    {
        s_assert(data != nullptr);
        ResourceID id = InvalidResourceID;
        auto width = 0;
        auto height = 0;
        auto mipmap = 1;
        auto componets = 0;
        stbi_set_unpremultiply_on_load(1);
        stbi_convert_iphone_png_to_rgb(1);
        auto status = stbi_info_from_memory(data->GetBuffer(), data->GetSize(), &width, &height, &componets);
        if (status == 1 && width > 0 && height > 0)
        {
            auto buffer = stbi_load_from_memory(data->GetBuffer(), data->GetSize(), &width, &height, &componets, STBI_rgb_alpha);

            auto temp = reinterpret_cast<uint32 *>(buffer);
            for (auto i = 0; i < width * height; ++i)
            {
                temp[i] = RGB_PREMULTIPLY_ALPHA(buffer[i * 4], buffer[i * 4 + 1], buffer[i * 4 + 2], buffer[i * 4 + 3]);
            }
            data->Copy(buffer, width * height * 4);
            stbi_image_free(buffer);
            auto config = TextureConfig::FromData(width, height, mipmap, TextureType::TEXTURE_2D, PixelFormat::RGBA8);
            config.Name = ResourceName::Shared(location);
            config.FilterModeMin = antiAlias ? TextureFilterMode::LINEAR : TextureFilterMode::NEAREST;
            config.FilterModeMag = antiAlias ? TextureFilterMode::LINEAR : TextureFilterMode::NEAREST;
            config.DataOffset[0][0] = 0;
            config.DataSize[0][0] = data->GetSize();
            id = GetGraphics().GetResourceManager().Create(config, data);
        }
        else
        {
            gliml::context context;
            context.enable_dxt(true);
            context.enable_pvrtc(true);
            context.enable_etc2(true);
            if (context.load(data->GetBuffer(), data->GetSize()))
            {
                width = context.image_width(0, 0);
                height = context.image_height(0, 0);
                mipmap = context.num_mipmaps(0);
                auto faces = context.num_faces();
                s_assert(mipmap <= GraphicsConfig::MaxTextureMipMapCount);
                auto format = PixelFormat::NONE;
                switch (context.image_internal_format())
                {
                case GLIML_GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
                    format = PixelFormat::DXT1;
                    break;
                case GLIML_GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
                    format = PixelFormat::DXT3;
                    break;
                case GLIML_GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
                    format = PixelFormat::DXT5;
                    break;
                case GLIML_GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG:
                    format = PixelFormat::PVRTC4_RGB;
                    break;
                case GLIML_GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG:
                    format = PixelFormat::PVRTC2_RGB;
                    break;
                case GLIML_GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:
                    format = PixelFormat::PVRTC4_RGBA;
                    break;
                case GLIML_GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:
                    format = PixelFormat::PVRTC2_RGBA;
                    break;
                case GLIML_GL_COMPRESSED_RGB8_ETC2:
                    format = PixelFormat::ETC2_RGB8;
                    break;
                case GLIML_GL_COMPRESSED_SRGB8_ETC2:
                    format = PixelFormat::ETC2_SRGB8;
                    break;
                case GLIML_GL_RGB:
                    if (context.image_type() == GLIML_GL_UNSIGNED_BYTE)
                    {
                        format = PixelFormat::RGB8;
                    }
                    else if (context.image_type() == GLIML_GL_UNSIGNED_SHORT_5_6_5)
                    {
                        format = PixelFormat::R5G6B5;
                    }
                    break;
                case GLIML_GL_RGBA:
                    switch (context.image_type())
                    {
                    case GLIML_GL_UNSIGNED_BYTE:
                        format = PixelFormat::RGBA8;
                        break;
                    case GLIML_GL_UNSIGNED_SHORT_4_4_4_4:
                        format = PixelFormat::RGBA4;
                        break;
                    case GLIML_GL_UNSIGNED_SHORT_5_5_5_1:
                        format = PixelFormat::R5G5B5A1;
                        break;
                    default:
                        break;
                    }
                    break;
                default:
                    break;
                }
                s_assert(format != PixelFormat::NONE);
                auto type = TextureType::TEXTURE_2D;
                switch (context.texture_target())
                {
                case GLIML_GL_TEXTURE_2D:
                    type = TextureType::TEXTURE_2D;
                    break;
                case GLIML_GL_TEXTURE_3D:
                    type = TextureType::TEXTURE_3D;
                    break;
                case GLIML_GL_TEXTURE_CUBE_MAP:
                    type = TextureType::TEXTURE_CUBE;
                    break;
                default:
                    s_error("Unknown texture type!\n");
                    break;
                }
                auto config = TextureConfig::FromData(width, height, mipmap, type, format);
                config.Name = ResourceName::Shared(location);
                if (config.MipMapCount > 1)
                {
                    config.FilterModeMin = antiAlias ? TextureFilterMode::LINEAR_MIPMAP_NEAREST : TextureFilterMode::NEAREST;
                    config.FilterModeMag = antiAlias ? TextureFilterMode::LINEAR_MIPMAP_NEAREST : TextureFilterMode::NEAREST;
                }
                else
                {
                    config.FilterModeMin = antiAlias ? TextureFilterMode::LINEAR : TextureFilterMode::NEAREST;
                    config.FilterModeMag = antiAlias ? TextureFilterMode::LINEAR : TextureFilterMode::NEAREST;
                }
                for (auto i = 0; i < faces; ++i)
                {
                    for (auto j = 0; j < context.num_mipmaps(i); ++j)
                    {
                        auto p = reinterpret_cast<const uchar *>(context.image_data(i, j));
                        config.DataOffset[i][j] = p - data->GetBuffer();
                        config.DataSize[i][j] = context.image_size(i, j);
                    }
                }
                id = GetGraphics().GetResourceManager().Create(config, data);
            }
        }
        return id;
    }

    ResourceID TextureLoader::LoadFromLocation(const std::string &location, bool antiAlias)
    {
        auto resourceName = ResourceName::Shared(location);
        auto resourceID = GetGraphics().GetResourceManager().Find(resourceName);

        if (resourceID == InvalidResourceID)
        {
            auto data = GetIO().Read(resourceName.GetName());
            if (data)
            {
                resourceID = LoadFromData(location, antiAlias, data);
            }
        }

        return resourceID;
    }

    void TextureLoader::AsyncLoadFromLocation(const std::string &location, bool antiAlias, TextureLoaderCallback callback)
    {
        s_assert(callback != nullptr);

        auto resourceName = ResourceName::Shared(location);
        auto resourceID = GetGraphics().GetResourceManager().Find(resourceName);

        if (resourceID != InvalidResourceID)
        {
            callback(resourceID);
        }
        else
        {
            GetIO().AsyncRead(resourceName.GetName(), [location, antiAlias, callback](EventPtr e)
            {
                if (e->GetStatus() != EventStatus::COMPLETE)
                {
                    callback(InvalidResourceID);
                }
                auto data = std::static_pointer_cast<IORequestReadEvent>(e)->GetData();
                if (data == nullptr)
                {
                    callback(InvalidResourceID);
                }
                callback(LoadFromData(location, antiAlias, data));
            });
        }
    }
}