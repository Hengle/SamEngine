#pragma once

#include "texture.h"
#include "texture_factory.h"

#include "graphics/config/texture_config.h"
#include "graphics/config/graphics_config.h"

#include "resource/resource_pool.h"
#include "resource/resource_manager.h"

namespace sam
{
    typedef resource_pool<texture, texture_config> texture_pool;

    class graphics_resource_manager : public resource_manager
    {
    public:
        graphics_resource_manager();

        virtual ~graphics_resource_manager();

        void initialize(const graphics_config &config);

        void finalize();

        resource::id create(const texture_config &config);

    private:
        texture_pool texture_pool;
        texture_factory texture_factory;
    };
}