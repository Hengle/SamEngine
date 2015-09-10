#include "gl_shader_factory.h"

#include "graphics/renderer/renderer.h"

namespace sam
{
    resource::status gl_shader_factory::create(shader &shader, data_ptr data)
    {
        attribute.renderer->reset_shader();

        auto &config = shader.config;

        auto vertex_shader = compile_shader(gl::from_shader_type(shader_type::vertex_shader), config.vertex_shader_source.c_str(), config.vertex_shader_source.length());
        auto fragment_shader = compile_shader(gl::from_shader_type(shader_type::fragment_shader), config.fragment_shader_source.c_str(), config.fragment_shader_source.length());

        s_assert(vertex_shader != 0 && fragment_shader != 0);

        shader.program = link_program(vertex_shader, fragment_shader);

        s_assert(shader.program != 0);

        attribute.renderer->bind_program(shader.program);
        
        auto texture_index = 0;
        for (auto index = 0; index < config.uniforms.length(); ++index)
        {
            auto &uniform = config.uniforms.at(index);
            auto location = glGetUniformLocation(shader.program, uniform.get_name().c_str());
            shader.uniform_locations[index] = location;
            if (uniform.get_type() == uniform_format::texture)
            {
                shader.uniform_locations[index] = texture_index;
                glUniform1i(location, texture_index);
                ++texture_index;
                s_assert(texture_index <= graphics_config::max_texture_count);
            }
        }

        attribute.renderer->reset_shader();

        return resource::status::completed;
    }

    void gl_shader_factory::destroy(shader &shader)
    {
        attribute.renderer->reset_shader();

        glDeleteProgram(shader.program);
    }

    GLuint gl_shader_factory::compile_shader(GLenum type, const char *source, int32 length)
    {
        s_assert(source != nullptr && length > 0);

        auto shader = glCreateShader(type);

        s_assert(shader != 0);

        glShaderSource(shader, 1, &source, &length);
        glCompileShader(shader);

        auto status = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

        #if SAM_DEBUG
        auto log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);
        if (status == GL_FALSE && log_length > 0)
        {
            log::debug("[shader source]:\n%s\n\n", source);
            auto log = static_cast<GLchar *>(std::malloc(log_length));
            glGetShaderInfoLog(shader, log_length, &log_length, log);
            log::debug("[compile log]:\n%s\n\n", log);
            std::free(log);
        }
        #endif

        if (status == GL_FALSE)
        {
            glDeleteShader(shader);
            shader = 0;
        }

        return shader;
    }

    GLuint gl_shader_factory::link_program(GLuint vertex, GLuint fragment)
    {
        auto program = glCreateProgram();

        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        for (auto i = 0; i < graphics_config::max_vertex_node_count; ++i)
        {
            glBindAttribLocation(program, i, attribute_name(static_cast<vertex_attribute_type>(i)));
        }
        glLinkProgram(program);
        
        glDeleteShader(vertex);
        glDeleteShader(fragment);

        auto status = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &status);

        #if SAM_DEBUG
        auto log_length = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_length);
        if (status == GL_FALSE && log_length > 0)
        {
            auto log = static_cast<GLchar *>(std::malloc(log_length));
            glGetProgramInfoLog(program, log_length, &log_length, log);
            log::debug("[link log]:\n%s\n\n", log);
            std::free(log);
        }
        #endif

        if (status == GL_FALSE)
        {
            glDeleteProgram(program);
            program = 0;
        }

        return program;
    }
}