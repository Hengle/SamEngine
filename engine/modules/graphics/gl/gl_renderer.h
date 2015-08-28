#pragma once

#include "graphics/core/renderer_base.h"

namespace sam
{
    class gl_renderer : public renderer_base
    {
    public:
        gl_renderer();

        virtual ~gl_renderer();

        virtual void apply_target(std::shared_ptr<texture_base> texture, const clear_state& state) override;
    };
}