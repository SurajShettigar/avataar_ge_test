#ifndef MATERIAL_TEST_SCENE_HPP
#define MATERIAL_TEST_SCENE_HPP

#include "globals.hpp"

#include "camera.hpp"
#include "shader.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "object.hpp"

class Scene {
public:
    Scene() = default;

    ~Scene() = default;

    [[nodiscard]] inline Camera &getCamera() {
        return m_camera;
    }

    [[nodiscard]] inline const std::vector<Object> &getObjects() const {
        return m_objects;
    }

    [[nodiscard]] inline std::vector<Object> &getObjects() {
        return m_objects;
    }


    [[nodiscard]] inline const std::vector<Mesh> &getMeshes() const {
        return m_meshes;
    }

    [[nodiscard]] inline const std::vector<Material> &getMaterials() const {
        return m_materials;
    }

    [[nodiscard]] inline const Mesh &getMesh(uint32_t mesh_id) const {
        return m_meshes.at(mesh_id);
    }

    [[nodiscard]] inline const Material &getMaterial(uint32_t mat_id) const {
        return m_materials.at(mat_id);
    }

    void initScene() const;

    static Scene getDefaultScene(uint32_t shader_pbr);

    static Scene getMaterialTestScene(uint32_t shader_pbr, uint32_t shader_debug_normal);

private:
    Camera m_camera = Camera{};
    std::vector<Material> m_materials = {};
    std::vector<Mesh> m_meshes = {};
    std::vector<Object> m_objects = {};
};


#endif //MATERIAL_TEST_SCENE_HPP
