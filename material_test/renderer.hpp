#ifndef MATERIAL_TEST_RENDERER_HPP
#define MATERIAL_TEST_RENDERER_HPP

#include "scene.hpp"

class Renderer {
public:
    Renderer() = default;

    ~Renderer() = default;

    // Disable copy
    Renderer(const Renderer &renderer) = delete;

    Renderer &operator=(const Renderer &renderer) = delete;

    bool init();

    void update(double x_pos, double y_pos);
    void render(int32_t width, int32_t height);

    void clean();

private:
    Shader m_shader_pbr = Shader{DEFAULT_SHADER_NAME};
    Shader m_shader_debug_normal = Shader{DEBUG_NORMAL_SHADER_NAME};
    Scene m_current_scene;

    uint32_t m_selected_object = INVALID_OPENGL_OBJECT_ID;
    uint32_t m_selected_mat = INVALID_OPENGL_OBJECT_ID;

    void toggleSelection(uint32_t curr_obj, uint32_t curr_mat);
};


#endif //MATERIAL_TEST_RENDERER_HPP
