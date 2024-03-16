#ifndef MATERIAL_TEST_SHADER_HPP
#define MATERIAL_TEST_SHADER_HPP

#include "globals.hpp"

class Shader {
public:
    Shader() = default;

    ~Shader() = default;

    explicit Shader(std::string shader_name);

    inline uint32_t getID() const {
        return m_shader;
    }

    void initShader() const;

    void bindShader() const;
private:
    std::string m_shader_name = DEFAULT_SHADER_NAME;
    mutable uint32_t m_vertex_shader = INVALID_OPENGL_OBJECT_ID;
    mutable uint32_t m_frag_shader = INVALID_OPENGL_OBJECT_ID;
    mutable uint32_t m_shader = INVALID_OPENGL_OBJECT_ID;
};


#endif //MATERIAL_TEST_SHADER_HPP
