#include "gl_shader_factory.h"

#include "graphics/renderer/renderer.h"

namespace sam
{
    resource::status gl_shader_factory::create(gl_shader &shader, data_ptr data)
    {
        attribute.renderer->reset_shader_state();

        auto config = shader.config;

        auto vertex_shader = compile_shader(gl::from_shader_type(shader_type::vertex_shader), config.vertex_shader_source.c_str(), config.vertex_shader_source.length());
        auto fragment_shader = compile_shader(gl::from_shader_type(shader_type::fragment_shader), config.fragment_shader_source.c_str(), config.fragment_shader_source.length());

        s_assert(vertex_shader != 0 && fragment_shader != 0);

        shader.program = link_program(vertex_shader, fragment_shader);

        s_assert(shader.program != 0);

        attribute.renderer->bind_program(shader.program);

        auto index = 0;
        for (auto uniform : config.uniforms)
        {
            s_assert(index < graphics_config::max_uniform_node_count);
            auto location = glGetUniformLocation(shader.program, uniform.name.c_str());
            shader.uniform_locations[index++] = location;
            // TODO bind sampler index
        }

        attribute.renderer->reset_shader_state();

        return resource::status::completed;
    }

    void gl_shader_factory::destroy(gl_shader &shader)
    {
        attribute.renderer->reset_shader_state();

        glDeleteProgram(shader.program);
        s_check_gl_error();
    }

    GLuint gl_shader_factory::compile_shader(GLenum type, const char *source, int32 length)
    {
        s_assert(source != nullptr && length > 0);

        auto shader = glCreateShader(type);
        s_check_gl_error();

        s_assert(shader != 0);

        glShaderSource(shader, 1, &source, &length);
        s_check_gl_error();

        glCompileShader(shader);
        s_check_gl_error();

        auto status = 0;

        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        s_check_gl_error();

        #if SAM_DEBUG
        auto log_length = 0;
        
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        s_check_gl_error();

        if (status != 0 && log_length > 0)
        {
            log::debug("[shader source]:\n%s\n\n", source);

            auto log = static_cast<GLchar *>(std::malloc(log_length));
            glGetShaderInfoLog(shader, log_length, &log_length, log);
            s_check_gl_error();

            log::debug("[compile log]:\n%s\n\n", log);
            std::free(log);
        }
        #endif

        if (status == GL_FALSE)
        {
            glDeleteShader(shader);
            s_check_gl_error();

            shader = 0;
        }

        return shader;
    }

    GLuint gl_shader_factory::link_program(GLuint vertex, GLuint fragment)
    {
        auto program = glCreateProgram();

        glAttachShader(program, vertex);
        s_check_gl_error();

        glAttachShader(program, fragment);
        s_check_gl_error();

        for (auto i = 0; i < graphics_config::max_vertex_node_count; ++i)
        {
            glBindAttribLocation(program, i, attribute_name(static_cast<vertex_attribute_type>(i)));
            s_check_gl_error();
        }

        glLinkProgram(program);
        s_check_gl_error();

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        auto status = 0;

        glGetProgramiv(program, GL_LINK_STATUS, &status);
        s_check_gl_error();

        #if SAM_DEBUG
        auto log_length = 0;

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        s_check_gl_error();

        if (status != 0 && log_length > 0)
        {
            auto log = static_cast<GLchar *>(std::malloc(log_length));
            glGetProgramInfoLog(program, log_length, &log_length, log);
            s_check_gl_error();

            log::debug("[link log]:\n%s\n\n", log);
            std::free(log);
        }
        #endif

        if (status == GL_FALSE)
        {
            glDeleteProgram(program);
            s_check_gl_error();

            program = 0;
        }

        return program;
    }
}