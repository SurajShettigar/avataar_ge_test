#include "camera.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

void Camera::bindBuffer() const {
    if (m_data_buffer == INVALID_OPENGL_OBJECT_ID) {
        glGenBuffers(1, &m_data_buffer);
        glBindBuffer(GL_UNIFORM_BUFFER, m_data_buffer);
        glBufferData(GL_UNIFORM_BUFFER, sizeof(CameraData), nullptr, GL_STATIC_DRAW);
        glBindBuffer(GL_UNIFORM_BUFFER, SHADER_UNIFORM_BINDING_CAM_DATA);
        glBindBufferRange(GL_UNIFORM_BUFFER, SHADER_UNIFORM_BINDING_CAM_DATA, m_data_buffer, 0, sizeof(CameraData));
    }

    glBindBuffer(GL_UNIFORM_BUFFER, m_data_buffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(CameraData), &m_data);
    glBindBuffer(GL_UNIFORM_BUFFER, SHADER_UNIFORM_BINDING_CAM_DATA);
}

glm::vec3 Camera::screenToWorldPosition(
        const glm::vec3 &screenPos) const {
    glm::vec4 pos(screenPos, 1.0f);
    pos[0] = (pos[0] / static_cast<float>(m_width)) * 2.0f - 1.0f;
    pos[1] = 1.0f - (pos[1] / static_cast<float>(m_height)) * 2.0f;
    pos[2] = std::fmin(std::fmax(pos[2], 0.0f), 1.0f);

    pos = glm::inverse(m_data.proj_mat * m_data.view_mat) * pos;
    pos /= pos[3];
    return static_cast<glm::vec3>(pos);
}

glm::vec3 Camera::worldToScreenPosition(
        const glm::vec3 &worldPos) const {
    glm::vec4 pos =
            m_data.proj_mat * m_data.view_mat * glm::vec4(worldPos, 1.0f);

    pos /= pos[3];

    pos[0] = (pos[0] * 0.5f + 0.5f) * static_cast<float>(m_width);
    pos[1] = (pos[1] * 0.5f + 0.5f) * static_cast<float>(m_height);
    pos[2] = map(pos[2], 0.0f, 1.0f, DEFAULT_CAM_Z_NEAR, DEFAULT_CAM_Z_FAR);
    return static_cast<glm::vec3>(pos);
}


Ray Camera::screenPositionToRay(
        const glm::vec2 &screenPos) const {
    const glm::vec3 origin{m_data.position};
    glm::vec3 direction{
            screenToWorldPosition(glm::vec3(screenPos[0], screenPos[1], 1.0f)) - origin};
    direction = glm::normalize(direction);
    return Ray{origin, direction};
}
