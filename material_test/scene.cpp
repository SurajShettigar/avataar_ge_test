// Copyright 2024 Suraj Shettigar
// SPDX-License-Identifier: Apache-2.0

#include "scene.hpp"

#define TINYOBJLOADER_IMPLEMENTATION

#include <tiny_obj_loader.h>

Scene Scene::getDefaultScene() {
    Scene scene;
    scene.m_materials.push_back(Material::DEFAULT);
    scene.m_meshes.push_back(Mesh::DEFAULT);

    Object obj(scene.m_meshes.size() - 1, scene.m_materials.size() - 1);
    scene.m_objects.emplace_back(obj);
    return scene;
}

Scene Scene::getMaterialTestScene() {
    Scene scene{};

    tinyobj::ObjReaderConfig config;
    config.triangulate = true;
    config.mtl_search_path = "./";

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(MODEL_SPHERE_FILEPATH, config))
        return scene;

    const auto &attribs = reader.GetAttrib();
    const auto &shapes = reader.GetShapes();

    std::vector<Vertex> vertices{attribs.vertices.size()};
    std::vector<uint32_t> indices;
    for (const auto &s: shapes) {
        size_t offset = 0;
        for (size_t f = 0; f < s.mesh.num_face_vertices.size(); f++) {
            const size_t num_v = s.mesh.num_face_vertices[f];
            for (size_t v = 0; v < num_v; v++) {
                const auto i = s.mesh.indices[offset + v];
                indices.emplace_back(i.vertex_index);
                vertices[i.vertex_index].position.x = attribs.vertices[3 * i.vertex_index + 0];
                vertices[i.vertex_index].position.y = attribs.vertices[3 * i.vertex_index + 1];
                vertices[i.vertex_index].position.z = attribs.vertices[3 * i.vertex_index + 2];
                if (i.normal_index >= 0) {
                    vertices[i.vertex_index].normal.x = attribs.normals[3 * i.normal_index + 0];
                    vertices[i.vertex_index].normal.y = attribs.normals[3 * i.normal_index + 1];
                    vertices[i.vertex_index].normal.z = attribs.normals[3 * i.normal_index + 2];
                }
            }
            offset += num_v;
        }
    }
    scene.m_materials.push_back(Material::DEFAULT);
    Mesh mesh{vertices, indices};
    scene.m_meshes.emplace_back(mesh);

    scene.m_objects.reserve(36);
    for (size_t i = 0; i < 36; i++) {
        Object o{0, 0};
        glm::vec3 scale(0.25f);
        float x_pos = map(static_cast<float>(i % 6), 0.0f, 5.0f, -6.0f, 6.0f);
        float y_pos = map(static_cast<float>(i / 6), 0.0f, 5.0f, -6.0f, 6.0f);
        glm::vec3 pos(x_pos, y_pos, 0.0f);

        glm::mat4x4 transform(1.0f);
        transform = glm::scale(transform, scale);
        transform = glm::translate(transform, pos);

        o.setTransform(transform);

        scene.m_objects.emplace_back(o);
    }

    return scene;
}
