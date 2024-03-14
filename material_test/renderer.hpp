#ifndef MATERIAL_TEST_RENDERER_HPP
#define MATERIAL_TEST_RENDERER_HPP

#include "scene.hpp"

class Renderer {
public:
    Renderer() : m_current_scene{Scene::getMaterialTestScene()} {};

    ~Renderer() = default;

    // Disable copy
    Renderer(const Renderer &renderer) = delete;

    Renderer &operator=(const Renderer &renderer) = delete;

    bool init();

    void render(float aspect_ratio);

    void clean();

private:
    Scene m_current_scene;
};


#endif //MATERIAL_TEST_RENDERER_HPP
