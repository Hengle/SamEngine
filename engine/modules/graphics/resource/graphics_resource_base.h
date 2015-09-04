#pragma once

#include "graphics/config/mesh_config.h"
#include "graphics/config/shader_config.h"
#include "graphics/config/texture_config.h"
#include "graphics/config/draw_state_config.h"

#include <resource/resource.h>

namespace sam
{
    class mesh_base : public resource_base<mesh_config> {};

    class shader_base : public resource_base<shader_config> {};

    class texture_base : public resource_base<texture_config> {};

    class draw_state_base : public resource_base<draw_state_config> {};
}