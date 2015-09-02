#include "graphics_resource_manager.h"

#include "graphics/core/define.h"

namespace sam
{
    void graphics_resource_manager::initialize(const graphics_config &config, const graphics_attribute &attribute)
    {
        this->attribute = attribute;
        mesh_pool.initialize(config.mesh_pool_size, static_cast<uint16>(graphics_resource_type::mesh));
        shader_pool.initialize(config.shader_pool_size, static_cast<uint16>(graphics_resource_type::shader));
        texture_pool.initialize(config.texture_pool_size, static_cast<uint16>(graphics_resource_type::texture));
        draw_state_pool.initialize(config.draw_state_pool_size, static_cast<uint16>(graphics_resource_type::draw_state));
        mesh_factory.initialize(attribute);
        shader_factory.initialize(attribute);
        texture_factory.initialize(attribute);
        draw_state_factory.initialize(attribute);
        resource_manager::initialize(config.registry_size);
    }

    void graphics_resource_manager::finalize()
    {
        attribute = graphics_attribute();
        mesh_pool.finalize();
        shader_pool.finalize();
        texture_pool.finalize();
        draw_state_pool.finalize();
        mesh_factory.finalize();
        shader_factory.finalize();
        texture_factory.finalize();
        draw_state_factory.finalize();
        resource_manager::finalize();
    }

    template <>
    resource::id graphics_resource_manager::create<mesh_config>(const mesh_config& config, data_ptr data)
    {
        auto id = registry.find(config.name);
        if (id == resource::invalid_id)
        {
            id = mesh_pool.create();
            registry.add(config.name, id, label_stack.top());
            auto &mesh = mesh_pool.get_resource(id, config);
            mesh.status = mesh_factory.create(mesh, data);
            s_assert(mesh.status != resource::status::invalid);
        }
        return id;
    }

    template <>
    resource::id graphics_resource_manager::create<shader_config>(const shader_config& config, data_ptr data)
    {
        auto id = registry.find(config.name);
        if (id == resource::invalid_id)
        {
            id = shader_pool.create();
            registry.add(config.name, id, label_stack.top());
            auto &shader = shader_pool.get_resource(id, config);
            shader.status = shader_factory.create(shader, data);
            s_assert(shader.status != resource::status::invalid);
        }
        return id;
    }

    template <>
    resource::id graphics_resource_manager::create<texture_config>(const texture_config& config, data_ptr data)
    {
        auto id = registry.find(config.name);
        if (id == resource::invalid_id)
        {
            id = texture_pool.create();
            registry.add(config.name, id, label_stack.top());
            auto &texture = texture_pool.get_resource(id, config);
            texture.status = texture_factory.create(texture, data);
            s_assert(texture.status != resource::status::invalid);
        }
        return id;
    }

    template <>
    resource::id graphics_resource_manager::create<draw_state_config>(const draw_state_config& config, data_ptr data)
    {
        auto id = registry.find(config.name);
        if (id == resource::invalid_id)
        {
            id = draw_state_pool.create();
            registry.add(config.name, id, label_stack.top());
            auto &draw_state = draw_state_pool.get_resource(id, config);
            draw_state.status = draw_state_factory.create(draw_state, data);
            s_assert(draw_state.status != resource::status::invalid);
        }
        return id;
    }

    void graphics_resource_manager::destroy(resource::label label)
    {
        auto all = registry.remove(label);
        for (auto id : all)
        {
            switch (static_cast<graphics_resource_type>(resource::get_pool_id(id)))
            {
            case graphics_resource_type::mesh:
            {
                auto mesh = mesh_pool.find_resource(id);
                if (mesh)
                {
                    mesh_factory.destroy(*mesh);
                    mesh_pool.destory(id);
                }
                break;
            }
            case graphics_resource_type::shader:
            {
                auto shader = shader_pool.find_resource(id);
                if (shader)
                {
                    shader_factory.destroy(*shader);
                    shader_pool.destory(id);
                }
                break;
            }
            case graphics_resource_type::texture:
            {
                auto texture = texture_pool.find_resource(id);
                if (texture)
                {
                    texture_factory.destroy(*texture);
                    texture_pool.destory(id);
                }
                break;
            }
            case graphics_resource_type::draw_state:
            {
                auto draw_state = draw_state_pool.find_resource(id);
                if (draw_state)
                {
                    draw_state_factory.destroy(*draw_state);
                    draw_state_pool.destory(id);
                }
                break;
            }
            default:
                s_error("unknown resource type");
                break;
            }
        }
    }
}