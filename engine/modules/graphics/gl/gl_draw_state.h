#pragma once

#include "graphics/resource/graphics_resource_base.h"

namespace sam
{
    class mesh;
    class shader;

    class gl_draw_state : public draw_state_base
    {
    public:
        mesh *mesh{ nullptr };

        shader *shader{ nullptr };

        virtual void finalize() override;
    };

    inline void gl_draw_state::finalize()
    {
        mesh = nullptr;
        shader = nullptr;
        draw_state_base::finalize();
    }
}