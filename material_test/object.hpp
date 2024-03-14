#ifndef MATERIAL_TEST_OBJECT_HPP
#define MATERIAL_TEST_OBJECT_HPP

#include "globals.hpp"

#include <glm/mat4x4.hpp>

class Object {
public:

    explicit Object(uint32_t mesh, uint32_t material) : m_mesh{mesh}, m_material{material} {};

    [[nodiscard]] inline uint32_t getMesh() const {
        return m_mesh;
    }

    [[nodiscard]] inline uint32_t getMaterial() const {
        return m_material;
    }

    [[nodiscard]] inline const glm::mat4x4 &getTransform() const {
        return m_transform;
    }

    [[nodiscard]] inline glm::mat4x4 getTransform() {
        return m_transform;
    }

    inline void setTransform(const glm::mat4x4 &mat) {
        m_transform = mat;
    }

private:
    uint32_t m_mesh = INVALID_OPENGL_OBJECT_ID;
    uint32_t m_material = INVALID_OPENGL_OBJECT_ID;
    glm::mat4x4 m_transform = glm::mat4x4(1.0f);
};


#endif //MATERIAL_TEST_OBJECT_HPP
