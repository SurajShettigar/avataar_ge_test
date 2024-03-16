#include "shader.hpp"

#include "file_manager.hpp"

#include <glad/glad.h>
#include <iostream>

Shader::Shader(std::string shader_name) : m_shader_name{std::move(shader_name)},
                                          m_vertex_shader{INVALID_OPENGL_OBJECT_ID},
                                          m_frag_shader{INVALID_OPENGL_OBJECT_ID} {
}

void Shader::initShader() const {
    const Filepath dir = Filepath(DEFAULT_SHADER_DIRECTORY);
    const Filepath v_shader_name = dir / Filepath(m_shader_name + DEFAULT_SHADER_EXTENSION_VERTEX);
    const Filepath f_shader_name = dir / Filepath(m_shader_name + DEFAULT_SHADER_EXTENSION_FRAGMENT);

    if (!fileExists(v_shader_name) || !fileExists(f_shader_name))
        return;

    std::vector<char> v_shader_source(getFileSize(v_shader_name));
    std::vector<char> f_shader_source(getFileSize(f_shader_name));

    if (readFile(v_shader_name, false, v_shader_source.data()) != v_shader_source.size())
        return;

    if (readFile(f_shader_name, false, f_shader_source.data()) != f_shader_source.size())
        return;

    m_vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    m_frag_shader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *v_data = v_shader_source.data();
    glShaderSource(m_vertex_shader, 1, &v_data, nullptr);
    glCompileShader(m_vertex_shader);

    int success;
    char log[512];
    glGetShaderiv(m_vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_vertex_shader, 512, NULL, log);
        std::cout << "Vertex Shader: " << v_shader_name << " failed to compile: " << log << std::endl;
    }

    const char *f_data = f_shader_source.data();
    glShaderSource(m_frag_shader, 1, &f_data, nullptr);
    glCompileShader(m_frag_shader);
    glGetShaderiv(m_frag_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(m_frag_shader, 512, NULL, log);
        std::cout << "Fragment Shader: " << f_shader_name << " failed to compile: " << log << std::endl;
    }

    m_shader = glCreateProgram();
    glAttachShader(m_shader, m_vertex_shader);
    glAttachShader(m_shader, m_frag_shader);
    glLinkProgram(m_shader);
    glGetProgramiv(m_shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_shader, 512, NULL, log);
        std::cout << "Shader: " << m_shader_name << " failed to compile: " << log << std::endl;
    }

    glDeleteShader(m_vertex_shader);
    glDeleteShader(m_frag_shader);
}

void Shader::bindShader() const {
    glUseProgram(m_shader);
}
