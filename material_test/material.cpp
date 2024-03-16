#include "material.hpp"

#include "file_manager.hpp"

#include <glad/glad.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

void Material::setMaterialData(const glm::mat4 &transform) const {
    // Set camera uniform block binding
    int32_t loc = glGetUniformBlockIndex(m_shader, SHADER_UNIFORM_NAME_CAM_DATA.c_str());
    if (loc > -1)
        glUniformBlockBinding(m_shader, loc, SHADER_UNIFORM_BINDING_CAM_DATA);

    // Set model transformation matrix
    loc = glGetUniformLocation(m_shader, SHADER_UNIFORM_NAME_TRANSFORM.c_str());
    if (loc > -1)
        glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(transform));


    // Set material data
//    loc = glGetUniformBlockIndex(m_shader, SHADER_UNIFORM_NAME_MATERIAL_DATA.c_str());
//    if (loc > -1)
//        glUniformBlockBinding(m_shader, loc, SHADER_UNIFORM_BINDING_MATERIAL_DATA);
//
//    size_t data_size = alignSize(sizeof(MaterialData), 16);
//    if (m_data_buffer == INVALID_OPENGL_OBJECT_ID) {
//        glGenBuffers(1, &m_data_buffer);
//        glBindBuffer(GL_UNIFORM_BUFFER, m_data_buffer);
//        glBufferData(GL_UNIFORM_BUFFER, static_cast<GLintptr>(data_size), nullptr, GL_STATIC_DRAW);
//        glBindBuffer(GL_UNIFORM_BUFFER, SHADER_UNIFORM_BINDING_MATERIAL_DATA);
//        glBindBufferRange(GL_UNIFORM_BUFFER, SHADER_UNIFORM_BINDING_MATERIAL_DATA, m_data_buffer, 0,
//                          static_cast<GLintptr>(data_size));
//    }
//
//    glBindBuffer(GL_UNIFORM_BUFFER, m_data_buffer);
//    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(MaterialData), &m_data);
//    glBindBuffer(GL_UNIFORM_BUFFER, SHADER_UNIFORM_BINDING_MATERIAL_DATA);


    loc = glGetUniformLocation(m_shader, "baseColor");
    if (loc > -1)
        glUniform3fv(loc, 1, glm::value_ptr(m_data.baseColor));
    loc = glGetUniformLocation(m_shader, "metallic");
    if (loc > -1)
        glUniform1f(loc, m_data.metallic);
    loc = glGetUniformLocation(m_shader, "roughness");
    if (loc > -1)
        glUniform1f(loc, m_data.roughness);
}
