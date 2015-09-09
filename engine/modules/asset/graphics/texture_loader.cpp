#include "texture_loader.h"

#include <graphics/graphics.h>
#include <io/io.h>
#include <resource/resource.h>

#include <stb_image.h>
#include <gliml.h>

namespace sam
{
    void texture_loader::load(const std::string &location, texture_loader_callback callback)
    {
        s_assert(callback != nullptr);
        auto name = resource_name::shared(location);
        auto id = graphics::find_resource(name);
        if (id != resource::invalid_id)
        {
            callback(id);
        }
        else
        {
            io::read(name.get_name(), [callback](event_ptr &e)
            {
                if (e->get_status() == event::status::complete)
                {
                    auto data = std::static_pointer_cast<io_request_read_event>(e)->get_data();
                    auto width = 0;
                    auto height = 0;
                    auto mipmap = 1;
                    auto componets = 0;
                    auto status = stbi_info_from_memory(data->get_buffer(), data->get_size(), &width, &height, &componets);
                    if (status == 1 && width > 0 && height > 0)
                    {
                        auto buffer = stbi_load_from_memory(data->get_buffer(), data->get_size(), &width, &height, &componets, 4);
                        data->assign(buffer, width * height * 4);
                        auto config = texture_config::from_data(width, height, mipmap, texture_type::texture_2d, pixel_format::rgba8);
                        config.data_offset[0][0] = 0;
                        config.data_size[0][0] = data->get_size();
                        callback(graphics::create_resource(config, data));
                        return;
                    }
                    else
                    {
                        gliml::context context;
                        context.enable_dxt(true);
                        context.enable_pvrtc(true);
                        context.enable_etc2(true);
                        if (context.load(data->get_buffer(), data->get_size()))
                        {
                            width = context.image_width(0, 0);
                            height = context.image_height(0, 0);
                            mipmap = context.num_mipmaps(0);
                            auto faces = context.num_faces();
                            s_assert(mipmap <= graphics_config::max_texture_mipmap_count);
                            auto format = pixel_format::none;
                            switch (context.image_internal_format())
                            {
                            case GLIML_GL_COMPRESSED_RGBA_S3TC_DXT1_EXT:
                                format = pixel_format::dxt1;
                                break;
                            case GLIML_GL_COMPRESSED_RGBA_S3TC_DXT3_EXT:
                                format = pixel_format::dxt3;
                                break;
                            case GLIML_GL_COMPRESSED_RGBA_S3TC_DXT5_EXT:
                                format = pixel_format::dxt5;
                                break;
                            case GLIML_GL_COMPRESSED_RGB_PVRTC_4BPPV1_IMG:
                                format = pixel_format::pvrtc4_rgb;
                                break;
                            case GLIML_GL_COMPRESSED_RGB_PVRTC_2BPPV1_IMG:
                                format = pixel_format::pvrtc2_rgb;
                                break;
                            case GLIML_GL_COMPRESSED_RGBA_PVRTC_4BPPV1_IMG:
                                format = pixel_format::pvrtc4_rgba;
                                break;
                            case GLIML_GL_COMPRESSED_RGBA_PVRTC_2BPPV1_IMG:
                                format = pixel_format::pvrtc2_rgba;
                                break;
                            case GLIML_GL_COMPRESSED_RGB8_ETC2:
                                format = pixel_format::etc2_rgb8;
                                break;
                            case GLIML_GL_COMPRESSED_SRGB8_ETC2:
                                format = pixel_format::etc2_srgb8;
                                break;
                            case GLIML_GL_RGB:
                                if (context.image_type() == GLIML_GL_UNSIGNED_BYTE)
                                {
                                    format = pixel_format::rgb8;
                                }
                                else if (context.image_type() == GLIML_GL_UNSIGNED_SHORT_5_6_5)
                                {
                                    format = pixel_format::r5g6b5;
                                }
                                break;
                            case GLIML_GL_RGBA:
                                switch (context.image_type())
                                {
                                case GLIML_GL_UNSIGNED_BYTE:
                                    format = pixel_format::rgba8;
                                    break;
                                case GLIML_GL_UNSIGNED_SHORT_4_4_4_4:
                                    format = pixel_format::rgba4;
                                    break;
                                case GLIML_GL_UNSIGNED_SHORT_5_5_5_1:
                                    format = pixel_format::r5g5b5a1;
                                    break;
                                default:
                                    break;
                                }
                                break;
                            default:
                                break;
                            }
                            s_assert(format != pixel_format::none);
                            auto type = texture_type::texture_2d;
                            switch (context.texture_target())
                            {
                                case GLIML_GL_TEXTURE_2D:
                                    type = texture_type::texture_2d;
                                    break;
                                case GLIML_GL_TEXTURE_3D:
                                    type = texture_type::texture_3d;
                                    break;
                                case GLIML_GL_TEXTURE_CUBE_MAP:
                                    type = texture_type::texture_cube;
                                    break;
                                default:
                                    s_error("Unknown texture type!\n");
                                    break;
                            }
                            auto config = texture_config::from_data(width, height, mipmap, type, format);
                            for (auto i = 0; i < faces; ++i)
                            {
                                for (auto j = 0; j < context.num_mipmaps(i); ++j)
                                {
                                    auto p = reinterpret_cast<const uchar *>(context.image_data(i, j));
                                    config.data_offset[i][j] = p - data->get_buffer();
                                    config.data_size[i][j] = context.image_size(i, j);
                                }
                            }
                            callback(graphics::create_resource(config, data));
                            return;
                        }
                    }
                }
                callback(resource::invalid_id);
            });
        }
    }
}