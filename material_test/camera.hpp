#ifndef MATERIAL_TEST_CAMERA_HPP
#define MATERIAL_TEST_CAMERA_HPP

#include "globals.hpp"

#include "aabb.hpp"

#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/ext/matrix_clip_space.hpp>

struct CameraData {
    glm::vec4 position;
    glm::mat4x4 view_mat;
    glm::mat4x4 proj_mat;
};

class Camera {
public:

    Camera() : m_cam_extent{DEFAULT_CAM_ORTHO_SIZE / 2.0f},
               m_data{
                       glm::vec4{0.0f, 0.0f, 10.0f, 0.0f},
                       glm::lookAt(glm::vec3{0.0f, 0.0f, 10.0f}, glm::vec3{0.0f}, glm::vec3(0.0f, 1.0f, 0.0f)),
                       glm::orthoRH(-m_cam_extent, m_cam_extent,
                                    -m_cam_extent, m_cam_extent,
                                    DEFAULT_CAM_Z_NEAR,
                                    DEFAULT_CAM_Z_FAR),

               }, m_data_buffer{INVALID_OPENGL_OBJECT_ID} {
    }

    Camera(glm::vec3 pos, glm::vec3 look_at_pos, float cam_size)
            : m_cam_extent{cam_size / 2.0f},
              m_data{
                      glm::vec4(pos, 0.0f),
                      glm::lookAt(pos, look_at_pos, glm::vec3(0.0f, 1.0f, 0.0f)),
                      glm::orthoRH(-m_cam_extent / 2.0f, m_cam_extent / 2.0f, -m_cam_extent / 2.0f,
                                   m_cam_extent / 2.0f, DEFAULT_CAM_Z_NEAR, DEFAULT_CAM_Z_FAR)
              }, m_data_buffer{INVALID_OPENGL_OBJECT_ID} {}

    inline void setAspectRatio(int32_t width, int32_t height) {
        m_width = width;
        m_height = height;
        float aspect_ratio = static_cast<float>(width) / static_cast<float>(height);
        m_data.proj_mat = glm::orthoRH(-m_cam_extent * aspect_ratio, m_cam_extent * aspect_ratio, -m_cam_extent,
                                       m_cam_extent, DEFAULT_CAM_Z_NEAR, DEFAULT_CAM_Z_FAR);
    }

    [[nodiscard]] inline const CameraData &getCameraData() const {
        return m_data;
    }

    void bindBuffer() const;

    [[nodiscard]] inline uint32_t getBufferID() const {
        return m_data_buffer;
    }

    [[nodiscard]] glm::vec3 screenToWorldPosition(
            const glm::vec3 &screenPos) const;

    [[nodiscard]] glm::vec3 worldToScreenPosition(
            const glm::vec3 &worldPos) const;

    [[nodiscard]] Ray screenPositionToRay(
            const glm::vec2 &screenPos) const;

private:
    float m_cam_extent = DEFAULT_CAM_ORTHO_SIZE;
    CameraData m_data = {};
    mutable uint32_t m_data_buffer = INVALID_OPENGL_OBJECT_ID;

    int32_t m_width = 0;
    int32_t m_height = 0;
};


#endif //MATERIAL_TEST_CAMERA_HPP
