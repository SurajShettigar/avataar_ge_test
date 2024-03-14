// Copyright 2024 Suraj Shettigar
// SPDX-License-Identifier: Apache-2.0

#ifndef MATERIAL_TEST_MESH_HPP
#define MATERIAL_TEST_MESH_HPP

#include "globals.hpp"

#include <glm/vec3.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
};

class Mesh {
public:
    Mesh() = default;

    ~Mesh() = default;

    explicit Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices);

    void initBuffers() const;
    void bindBuffers() const;
    void draw() const;

    static const Mesh DEFAULT;
private:
    std::vector<Vertex> m_vertices = {};
    std::vector<uint32_t> m_indices = {};
    mutable uint32_t m_vao = INVALID_OPENGL_OBJECT_ID;
    mutable uint32_t m_vbo = INVALID_OPENGL_OBJECT_ID;
    mutable uint32_t m_ebo = INVALID_OPENGL_OBJECT_ID;
};


#endif //MATERIAL_TEST_MESH_HPP
