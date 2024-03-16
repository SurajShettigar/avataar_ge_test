#ifndef MATERIAL_TEST_MATERIAL_HPP
#define MATERIAL_TEST_MATERIAL_HPP

#include <utility>

#include "globals.hpp"
#include "shader.hpp"

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

struct MaterialData {
    glm::vec3 baseColor = glm::vec4{0.5f, 0.5f, 0.5f, 1.0f};
    float metallic = 0.0f;
    float roughness = 0.5f;
};

class Material {
public:
    explicit Material(uint32_t shader, const glm::vec3 &color, float metallic, float roughness) :
            m_shader{shader},
            m_data{color, metallic, roughness},
            m_data_buffer{INVALID_OPENGL_OBJECT_ID} {};

    explicit Material(uint32_t shader) :
            m_shader{shader},
            m_data{},
            m_data_buffer{INVALID_OPENGL_OBJECT_ID} {};

    [[nodiscard]] inline uint32_t getShader() const {
        return m_shader;
    }

    void setMaterialData(const glm::mat4 &transform) const;

private:
    uint32_t m_shader = INVALID_OPENGL_OBJECT_ID;
    MaterialData m_data = MaterialData{};
    mutable uint32_t m_data_buffer = INVALID_OPENGL_OBJECT_ID;
};

#endif //MATERIAL_TEST_MATERIAL_HPP
