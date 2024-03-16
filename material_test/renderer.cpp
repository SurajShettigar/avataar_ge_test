#include <iostream>
#include "renderer.hpp"

bool Renderer::init() {
    m_shader_pbr.initShader();
    m_shader_debug_normal.initShader();
    m_current_scene = Scene::getMaterialTestScene(m_shader_pbr.getID(), m_shader_debug_normal.getID());
    m_current_scene.initScene();
    return true;
}

void toggleSelection(uint32_t curr_obj, uint32_t curr_mat) {
    if (curr_obj == INVALID_OPENGL_OBJECT_ID) {

    }
}

void Renderer::update(double x_pos, double y_pos) {

    glm::vec3 wPos = m_current_scene.getCamera().screenToWorldPosition(glm::vec3{x_pos, y_pos, 0.0f});

    auto &objs = m_current_scene.getObjects();
    for (size_t i = 0; i < objs.size(); i++) {
        AABB bounds = m_current_scene.getMesh(objs[i].getMesh()).getBounds();
        bounds = objs[i].transformAABB(bounds);
        if (bounds.contains(glm::vec3{wPos.x, wPos.y, 0.0f})) {

           if (m_selected_object == i) {
                objs[i].setMaterial(m_selected_mat);
                m_selected_object = INVALID_OPENGL_OBJECT_ID;
                m_selected_mat = INVALID_OPENGL_OBJECT_ID;
                return;
            }
           else if(m_selected_object != INVALID_OPENGL_OBJECT_ID) {
               objs[m_selected_object].setMaterial(m_selected_mat);
               m_selected_object = INVALID_OPENGL_OBJECT_ID;
               m_selected_mat = INVALID_OPENGL_OBJECT_ID;
           }

            m_selected_object = i;
            m_selected_mat = objs[i].getMaterial();
            objs[i].setMaterial(0);
            return;
        }
    }

    if (m_selected_object != INVALID_OPENGL_OBJECT_ID) {
        objs[m_selected_object].setMaterial(m_selected_mat);
        m_selected_object = INVALID_OPENGL_OBJECT_ID;
        m_selected_mat = INVALID_OPENGL_OBJECT_ID;
    }
}

void Renderer::render(int32_t width, int32_t height) {
    m_current_scene.getCamera().setAspectRatio(width, height);

    uint32_t prev_shader = -1;
    uint32_t prev_mesh = -1;
    for (const auto &o: m_current_scene.getObjects()) {
        const Material &mat = m_current_scene.getMaterial(o.getMaterial());
        const uint32_t curr_shader = mat.getShader();

        if (prev_shader != curr_shader) {
            prev_shader = curr_shader;
            if (curr_shader == m_shader_pbr.getID())
                m_shader_pbr.bindShader();
            else
                m_shader_debug_normal.bindShader();
        }
        mat.setMaterialData(o.getTransform());
        m_current_scene.getCamera().bindBuffer();

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
