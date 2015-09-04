#include "gl_draw_state_factory.h"

#include "graphics/renderer/renderer.h"
#include "graphics/resource/graphics_resource_manager.h"

namespace sam
{
    resource::status gl_draw_state_factory::create(draw_state &draw_state, data_ptr data)
    {
        auto config = draw_state.config;

        s_assert(config.mesh != resource::invalid_id && config.shader != resource::invalid_id);

        draw_state.mesh = attribute.mesh_pool->find_resource(config.mesh);
        draw_state.shader = attribute.shader_pool->find_resource(config.shader);

        s_assert(draw_state.mesh != nullptr && draw_state.shader != nullptr);

        return resource::status::completed;
    }

    void gl_draw_state_factory::destroy(draw_state &draw_state)
    {
        attribute.renderer->reset_mesh();
    }
}