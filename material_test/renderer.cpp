#include "renderer.hpp"

bool Renderer::init() {
    for (const auto &m: m_current_scene.getMaterials())
        m.initMaterial();
    for (const auto &m: m_current_scene.getMeshes())
        m.initBuffers();
    return true;
}

void Renderer::render(float aspect_ratio) {
    uint32_t prev_mat = -1;
    uint32_t prev_mesh = -1;

    m_current_scene.getCamera().setAspectRatio(aspect_ratio);
    const auto &viewProjMat = m_current_scene.getCamera().getProjMatrix() * m_current_scene.getCamera().getViewMatrix();
    for (const auto &o: m_current_scene.getObjects()) {
        const Material &mat = m_current_scene.getMaterial(o.getMaterial());
        if (prev_mat != o.getMaterial()) {
            prev_mat = o.getMaterial();
            mat.bindMaterial();
        }
        const glm::mat4x4 transform = viewProjMat * o.getTransform();
        mat.setTransformData(transform);

        const Mesh &mesh = m_current_scene.getMesh(o.getMesh());
        if (prev_mesh != o.getMesh()) {
            prev_mesh = o.getMesh();
            mesh.bindBuffers();
        }
        mesh.draw();
    }
}

void Renderer::clean() {

}
