#pragma once

#include "clear_state.h"
#include "texture_base.h"

#include <memory>

namespace sam
{
    class renderer_base
    {
    public:
        virtual ~renderer_base() {}

        virtual void apply_target(std::shared_ptr<texture_base> texture, const clear_state &state) {}
    };
}