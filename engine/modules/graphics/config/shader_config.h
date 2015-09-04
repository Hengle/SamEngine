#pragma once

#include "graphics/core/uniform_layout.h"

#include <resource/resource_name.h>

#include <string>

namespace sam
{
    class shader_config
    {
    public:
        static shader_config from_source(const std::string &vertex, const std::string &fragment);

        resource_name name{ resource_name::unique() };

        std::string vertex_shader_source;

        std::string fragment_shader_source;

        uniform_layout uniforms;
    };

    inline shader_config shader_config::from_source(const std::string &vertex, const std::string &fragment)
    {
        shader_config config;
        config.vertex_shader_source = vertex;
        config.fragment_shader_source = fragment;
        return config;
    }
}