#ifndef MATERIAL_TEST_MATERIAL_HPP
#define MATERIAL_TEST_MATERIAL_HPP

#include <utility>

#include "globals.hpp"

#include <glm/mat4x4.hpp>

class Material {
public:
    Material() = default;

    ~Material() = default;

    explicit Material(std::string shader_name);

    void initMaterial() const;
    void bindMaterial() const;

    void setTransformData(const glm::mat4 &mat) const;

    static const Material DEFAULT;
private:
    std::string m_shader_name = DEFAULT_SHADER_NAME;
    mutable uint32_t m_vertex_shader = INVALID_OPENGL_OBJECT_ID;
    mutable uint32_t m_frag_shader = INVALID_OPENGL_OBJECT_ID;
    mutable uint32_t m_shader = INVALID_OPENGL_OBJECT_ID;
};

#endif //MATERIAL_TEST_MATERIAL_HPP
