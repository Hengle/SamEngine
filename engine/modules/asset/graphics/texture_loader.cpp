#include "texture_loader.h"

#include <graphics/graphics.h>
#include <io/io.h>
#include <resource/resource.h>

#include <stb_image.h>

namespace sam
{
    void texture_loader::load(const std::string &location, texture_loader_callback callback)
    {
        s_assert(callback != nullptr);
        auto name = resource_name::shared(location);
        auto id = graphics::find_resource(name);
        if (id != resource::invalid_id)
        {
            callback(id);
        }
        else
        {
            io::read(name.get_name(), [callback](event_ptr &e)
            {
                if (e->get_status() == event::status::complete)
                {
                    auto data = std::static_pointer_cast<io_request_read_event>(e)->get_data();
                    auto width = 0;
                    auto height = 0;
                    auto componets = 0;
                    auto status = stbi_info_from_memory(data->get_buffer(), data->get_size(), &width, &height, &componets);
                    if (status == 1 && width > 0 && height > 0)
                    {
                        auto buffer = stbi_load_from_memory(data->get_buffer(), data->get_size(), &width, &height, &componets, 4);
                        data->assign(buffer, width * height * 4);
                        auto config = texture_config::from_data(width, height, 1, texture_type::texture_2d, pixel_format::rgba8);
                        callback(graphics::create_resource(config, data));
                    }
                }
                callback(resource::invalid_id);
            });
        }
    }
}