#ifndef MATERIAL_TEST_CAMERA_HPP
#define MATERIAL_TEST_CAMERA_HPP

#include "globals.hpp"

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

class Camera {
public:
    Camera() : m_cam_extent{DEFAULT_CAM_ORTHO_SIZE / 2.0f},
               m_transform{glm::lookAt(glm::vec3{0.0f, 0.0f, 10.0f}, glm::vec3{0.0f}, glm::vec3(0.0f, 1.0f, 0.0f))},
               m_projection{glm::orthoRH(-m_cam_extent, m_cam_extent,
                                         -m_cam_extent, m_cam_extent,
                                         DEFAULT_CAM_Z_NEAR,
                                         DEFAULT_CAM_Z_FAR)} {}

    Camera(glm::vec3 pos, glm::vec3 look_at_pos, float cam_size) {
        m_cam_extent = cam_size / 2.0f;
        m_transform = glm::lookAt(pos, look_at_pos, glm::vec3(0.0f, 1.0f, 0.0f));
        m_projection = glm::orthoRH(-m_cam_extent / 2.0f, m_cam_extent / 2.0f, -m_cam_extent / 2.0f,
                                    m_cam_extent / 2.0f, DEFAULT_CAM_Z_NEAR, DEFAULT_CAM_Z_FAR);
    }

    void setAspectRatio(float aspect_ratio) {
        m_projection = glm::orthoRH(-m_cam_extent * aspect_ratio, m_cam_extent * aspect_ratio, -m_cam_extent,
                                    m_cam_extent, DEFAULT_CAM_Z_NEAR, DEFAULT_CAM_Z_FAR);
    }

    [[nodiscard]] inline const glm::mat4x4 &getViewMatrix() const {
        return m_transform;
    }

    [[nodiscard]] inline const glm::mat4x4 &getProjMatrix() const {
        return m_projection;
    }

private:
    float m_cam_extent = DEFAULT_CAM_ORTHO_SIZE;
    glm::mat4x4 m_transform = glm::mat4x4(1.0f);
    glm::mat4x4 m_projection = glm::mat4x4(1.0f);
};


#endif //MATERIAL_TEST_CAMERA_HPP
