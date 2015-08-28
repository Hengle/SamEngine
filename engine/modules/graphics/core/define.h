#pragma once

#include <glm.hpp>

#undef assert

namespace sam
{
    typedef glm::vec4 color;

    enum class graphics_resource_type
    {
        texture,
        shader,
        mesh,
        draw_state,
        count,
    };
}