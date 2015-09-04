#pragma once

#include "graphics/resource/graphics_resource.h"
#include "graphics/resource/graphics_resource_factory.h"

namespace sam
{
    class gl_shader_factory : public graphics_resource_factory<shader>
    {
    public:
        virtual resource::status create(shader &shader, data_ptr data) override;

        virtual void destroy(shader &shader) override;

    private:
        GLuint compile_shader(GLenum type, const char *source, int32 length);

        GLuint link_program(GLuint vertex, GLuint fragment);
    };
}