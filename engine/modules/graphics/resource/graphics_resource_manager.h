#pragma once

#include "graphics_resource.h"

#include "graphics/attribute/graphics_attribute.h"

#include "graphics/config/mesh_config.h"
#include "graphics/config/shader_config.h"
#include "graphics/config/texture_config.h"
#include "graphics/config/draw_state_config.h"
#include "graphics/config/graphics_config.h"

#include <resource/resource_pool.h>
#include <resource/resource_manager.h>

#if defined(SAM_WINDOWS) || defined(SAM_OSX) || defined(SAM_MINGW)
#    include "graphics/gl/gl_mesh_factory.h"
#    include "graphics/gl/gl_shader_factory.h"
#    include "graphics/gl/gl_texture_factory.h"
#    include "graphics/gl/gl_draw_state_factory.h"
namespace sam
{
    class mesh_factory : public gl_mesh_factory {};
    class shader_factory : public gl_shader_factory {};
    class texture_factory : public gl_texture_factory {};
    class draw_state_factory : public gl_draw_state_factory {};
}
#endif

namespace sam
{
    class mesh_pool : public resource_pool<mesh, mesh_config> {};
    class shader_pool : public resource_pool<shader, shader_config> {};
    class texture_pool : public resource_pool<texture, texture_config> {};
    class draw_state_pool : public resource_pool<draw_state, draw_state_config> {};

    class graphics_resource_manager : public resource_manager
    {
    public:
        void initialize(const graphics_config &config, const graphics_attribute &attribute);

        virtual void finalize() override;

        template <class CONFIG>
        resource::id create(const CONFIG &config, data_ptr data);

        void destroy(resource::label label);

        template <class CONFIG>
        CONFIG &find_config(resource::id id);

    private:
        graphics_attribute attribute;

        mesh_pool mesh_pool;
        shader_pool shader_pool;
        texture_pool texture_pool;
        draw_state_pool draw_state_pool;

        mesh_factory mesh_factory;
        shader_factory shader_factory;
        texture_factory texture_factory;
        draw_state_factory draw_state_factory;

        friend class graphics;
    };
}