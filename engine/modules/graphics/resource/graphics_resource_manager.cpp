#include "graphics_resource_manager.h"

#include "graphics/core/define.h"

namespace sam
{
    graphics_resource_manager::graphics_resource_manager()
    {
    }

    graphics_resource_manager::~graphics_resource_manager()
    {
    }

    void graphics_resource_manager::initialize(const graphics_config &config)
    {
        texture_pool.initialize(config.texture_pool_size, static_cast<uint16>(graphics_resource_type::texture));
        resource_manager::initialize(config.registery_size);
    }

    void graphics_resource_manager::finalize()
    {
        resource_manager::finalize();
    }

    resource::id graphics_resource_manager::create(const texture_config& config)
    {
        auto id = registry.find(config.location);
        if (id == resource::invalid_id)
        {
            id = texture_pool.create();
            auto &texture = texture_pool.get_resource(id, config);
            texture.status = texture_factory.create(texture);
            s_assert(texture.status != resource::status::invalid);
        }
        return id;
    }
}