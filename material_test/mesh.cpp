#include "mesh.hpp"

#include "material.hpp"

#include <glad/glad.h>

const Mesh Mesh::DEFAULT{
        std::vector<Vertex>{Vertex{glm::vec3{-0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}},
                            Vertex{glm::vec3{0.5f, -0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}},
                            Vertex{glm::vec3{0.0f, 0.5f, 0.0f}, glm::vec3{0.0f, 0.0f, 1.0f}}},
        std::vector<uint32_t>{0, 1, 2}};

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<uint32_t> &indices)
        : m_vertices{vertices},
          m_indices{indices},
          m_vao{INVALID_OPENGL_OBJECT_ID},
          m_vbo{INVALID_OPENGL_OBJECT_ID}, m_ebo{INVALID_OPENGL_OBJECT_ID} {
}

void Mesh::initBuffers() const {
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);


    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(Vertex) * m_vertices.size()), m_vertices.data(),
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLintptr>(sizeof(uint32_t) * m_indices.size()), m_indices.data(),
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, position)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          reinterpret_cast<void *>(offsetof(Vertex, normal)));
    glEnableVertexAttribArray(1);
}

void Mesh::bindBuffers() const {
    glBindVertexArray(m_vao);
}

void Mesh::draw() const {
    glDrawElements(GL_TRIANGLES, static_cast<int32_t>(m_indices.size()), GL_UNSIGNED_INT, 0);
}
