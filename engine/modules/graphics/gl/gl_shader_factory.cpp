#include "gl_shader_factory.h"

namespace sam
{
    resource::status gl_shader_factory::create(gl_shader &shader, data_ptr data)
    {
        return resource::status::completed;
    }

    void gl_shader_factory::destroy(gl_shader &shader)
    {
    }
}