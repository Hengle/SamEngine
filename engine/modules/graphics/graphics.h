#pragma once

#include "config/graphics_config.h"
#include "resource/graphics_resource_manager.h"
#include "renderer/renderer.h"

namespace sam
{
    class graphics
    {
    public:
        static void initialize(const graphics_config &config);

        static void finalize();

        static bool available();

        static void render();

        static resource::label push_resource_label();

        static void push_resource_label(resource::label label);

        static void pop_resource_label();

        template <class CONFIG>
        static resource::id create_resource(const CONFIG &config, data_ptr data = nullptr);

        static resource::id find_resource(const resource_name name);

        static void destroy_resource(resource::label label);

        static void apply_default_target(const clear_state &state = clear_state());

        static void apply_render_target(resource::id target, const clear_state &state);

        static void apply_view_port(int32 x, int32 y, int32 width, int32 height);

        static void apply_scissor(int32 x, int32 y, int32 width, int32 height);

        static void apply_draw_state(resource::id state);

//        static void apply_uniform_data(int32 index, data_ptr data);

        // vertex

        static void draw(int32 index = 0);

        static void draw(const draw_call_attribute &attribute);

        static void reset();

    private:
        static class state
        {
        public:
            renderer renderer;

            graphics_resource_manager resource;
        } *graphics_state;
    };

    template <class CONFIG>
    resource::id graphics::create_resource(const CONFIG &config, data_ptr data)
    {
        s_assert(available());
        return graphics_state->resource.create(config, data);
    }
}