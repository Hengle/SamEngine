#include "gl_texture_factory.h"
#include "graphics/resource/graphics_resource.h"
#include "graphics/renderer/renderer.h"

namespace sam
{
    resource::status gl_texture_factory::create(texture &texture, data_ptr data)
    {
        s_assert(data != nullptr && !data->empty());

        auto config = texture.config;
        auto texture_attribute = config.attribute;

        texture.target = gl::from_texture_type(texture_attribute.type);
        
        attribute.renderer->reset_texture_state();

        glGenTextures(1, &texture.texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(texture.target, texture.texture);
        s_check_gl_error();

        s_assert(texture.texture != 0);
        s_assert(texture_attribute.mipmap_count == 1 || !filter_mode_use_mipmap(config.filter_min));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, gl::from_texture_filter_mode(config.filter_min));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, gl::from_texture_filter_mode(config.filter_mag));
        s_check_gl_error();

        s_assert(texture_attribute.type != texture_type::texture_cube || (config.wrap_mode_s == texture_wrap_mode::clamp_to_edge && config.wrap_mode_t == texture_wrap_mode::clamp_to_edge));

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, gl::from_texture_wrap_mode(config.wrap_mode_s));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, gl::from_texture_wrap_mode(config.wrap_mode_t));
        s_check_gl_error();

        auto face_count = texture_attribute.type == texture_type::texture_cube ? graphics_config::cube_texture_face_count : 1;
        auto is_compressed = is_compressed_format(texture_attribute.color_format);
        auto internal_format = gl::from_pixel_format_as_internal(texture_attribute.color_format);
        auto layout = gl::from_pixel_format_as_layout(texture_attribute.color_format);
        auto format = gl::from_pixel_format_as_format(texture_attribute.color_format);

        for (auto face_index = 0; face_index < face_count; ++face_index)
        {
            auto real_target = texture.target;
            if (texture_type::texture_cube == texture_attribute.type)
            {
                switch (face_index) {
                case 0: real_target = GL_TEXTURE_CUBE_MAP_POSITIVE_X; break;
                case 1: real_target = GL_TEXTURE_CUBE_MAP_NEGATIVE_X; break;
                case 2: real_target = GL_TEXTURE_CUBE_MAP_POSITIVE_Y; break;
                case 3: real_target = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y; break;
                case 4: real_target = GL_TEXTURE_CUBE_MAP_POSITIVE_Z; break;
                default: real_target = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z; break;
                }
            }
            for (auto mipmap_index = 0; mipmap_index < texture_attribute.mipmap_count; ++mipmap_index)
            {
                s_assert(config.data_size[face_index][mipmap_index] > 0);
                auto texture_width = texture_attribute.width >> mipmap_index;
                auto texture_height = texture_attribute.height >> mipmap_index;
                if (texture_width == 0) texture_width = 1;
                if (texture_height == 0) texture_height = 1;
                if (is_compressed)
                {
                    s_assert(config.data_offset[face_index][mipmap_index] + config.data_size[face_index][mipmap_index] <= data->get_size());
                    glCompressedTexImage2D(real_target, mipmap_index, internal_format, texture_width, texture_height, 0, config.data_size[face_index][mipmap_index], data->get_buffer() + config.data_offset[face_index][mipmap_index]);
                }
                else
                {
                    glTexImage2D(real_target, mipmap_index, internal_format, texture_width, texture_height, 0, format, layout, data->get_buffer() + config.data_offset[face_index][mipmap_index]);
                }
                s_check_gl_error();
            }
        }

        return resource::status::completed;
    }

    void gl_texture_factory::destroy(texture &texture)
    {
        attribute.renderer->reset_texture_state();

        if (texture.texture != 0)
        {
            glDeleteTextures(1, &texture.texture);
            s_check_gl_error();
        }
        if (texture.frame_buffer != 0)
        {
            glDeleteFramebuffers(1, &texture.frame_buffer);
            s_check_gl_error();
        }
        if (texture.depth_render_buffer != 0)
        {
            glDeleteRenderbuffers(1, &texture.depth_render_buffer);
            s_check_gl_error();
        }
    }
}