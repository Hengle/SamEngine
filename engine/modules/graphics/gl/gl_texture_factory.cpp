#include "gl_texture_factory.h"

namespace sam
{
    gl_texture_factory::gl_texture_factory()
    {
    }

    gl_texture_factory::~gl_texture_factory()
    {
    }

    resource::status gl_texture_factory::create(texture_base& texture)
    {
        return resource::status::failed;
    }
}