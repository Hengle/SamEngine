#pragma once

#include "graphics_config.h"
#include "graphics/attribute/texture_attribute.h"
#include "graphics/core/define.h"

#include <core/assert.h>
#include <core/types.h>

#include <resource/resource.h>
#include <resource/resource_name.h>

namespace sam
{
    class texture_config
    {
    public:
        static texture_config from_data(int32 width, int32 height, int32 mipmap_count, texture_type type, pixel_format format);

        resource_name name { resource_name::unique() };

        texture_attribute attribute;

        float32 real_width{ 0.0f };

        float32 real_height{ 0.0f };

        resource::id depth_render_target{ resource::invalid_id };

        texture_wrap_mode wrap_mode_s{ texture_wrap_mode::repeat };

        texture_wrap_mode wrap_mode_t{ texture_wrap_mode::repeat };

        texture_wrap_mode wrap_mode_r{ texture_wrap_mode::repeat };

        texture_filter_mode filter_min{ texture_filter_mode::nearest };

        texture_filter_mode filter_mag{ texture_filter_mode::nearest };

        int32 data_offset[graphics_config::cube_texture_face_count][graphics_config::max_texture_mipmap_count];
        int32 data_size[graphics_config::cube_texture_face_count][graphics_config::max_texture_mipmap_count];
    };

    inline texture_config texture_config::from_data(int32 width, int32 height, int32 mipmap_count, texture_type type, pixel_format format)
    {
        s_assert(width > 0 && height > 0);
        s_assert_range(mipmap_count, 0, graphics_config::max_texture_mipmap_count);

        texture_config config;
        config.attribute.width = width;
        config.attribute.height = height;
        config.attribute.mipmap_count = mipmap_count;
        config.attribute.type = type;
        config.attribute.color_format = format;
        return config;
    }
}