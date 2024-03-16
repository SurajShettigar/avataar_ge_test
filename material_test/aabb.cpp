#include "aabb.hpp"

#include <cmath>
#include <utility>

#include <glm/glm.hpp>

static constexpr float MACHINE_EPSILON_F =
        std::numeric_limits<float>::epsilon() * 0.5f;

inline constexpr float gammaf(int n) {
    return (static_cast<float>(n) * MACHINE_EPSILON_F) /
           (1.0f - static_cast<float>(n) * MACHINE_EPSILON_F);
}

AABB::AABB()
        : m_min{glm::vec3{1.0f} * std::numeric_limits<float>::max()},
          m_max{glm::vec3{1.0f} * std::numeric_limits<float>::lowest()} {};

AABB::AABB(const glm::vec3 &point)
        : m_min{point}, m_max{point} {};

AABB::AABB(const glm::vec3 &min, const glm::vec3 &max)
        : m_min{glm::vec3{std::fmin(min[0], max[0]), std::fmin(min[1], max[1]),
                          std::fmin(min[2], max[2])}},
          m_max{glm::vec3{std::fmax(min[0], max[0]), std::fmax(min[1], max[1]),
                          std::fmax(min[2], max[2])}} {};

bool AABB::operator==(const AABB &rhs) const {
    return m_min == rhs.m_min && m_max == rhs.m_max;
}

bool AABB::operator!=(const AABB &rhs) const {
    return !(*this == rhs);
}

void AABB::encapsulate(const glm::vec3 &point) {
    m_min =
            glm::vec3(std::fmin(m_min[0], point[0]), std::fmin(m_min[1], point[1]),
                      std::fmin(m_min[2], point[2]));
    m_max =
            glm::vec3(std::fmax(m_max[0], point[0]), std::fmax(m_max[1], point[1]),
                      std::fmax(m_max[2], point[2]));
}

void AABB::encapsulate(const AABB &bounds) {
    m_min = glm::vec3(std::fmin(m_min[0], bounds.m_min[0]),
                      std::fmin(m_min[1], bounds.m_min[1]),
                      std::fmin(m_min[2], bounds.m_min[2]));
    m_max = glm::vec3(std::fmax(m_max[0], bounds.m_max[0]),
                      std::fmax(m_max[1], bounds.m_max[1]),
                      std::fmax(m_max[2], bounds.m_max[2]));
}

void AABB::expand(float delta) {
    m_min -= glm::vec3{1.0f} * delta;
    m_max += glm::vec3{1.0f} * delta;
}

bool AABB::contains(const glm::vec3 &point) const {
    const bool x = (point[0] >= m_min[0]) && (point[0] <= m_max[0]);
    const bool y = (point[1] >= m_min[1]) && (point[1] <= m_max[1]);
    const bool z = (point[2] >= m_min[2]) && (point[2] <= m_max[2]);
    return x && y && z;
}

bool AABB::intersectWithRay(const Ray &ray,
                            glm::vec3 *enterPoint,
                            glm::vec3 *exitPoint) const {
    // Solved by intersecting ray with each plane-slabs. The plane equations
    // are used to solve the intersections.
    // Refer: Section 3.1.2, PBRT 3rd Edition, by Matt Pharr

    float t0 = 0.0f;
    float t1 = ray.getMaxDistance();

    for (size_t i = 0; i < 3; i++) {
        const float invRayDir = 1.0f / ray.getDirection()[i];
        float tNear = (m_min[i] - ray.getOrigin()[i]) * invRayDir;
        float tFar = (m_max[i] - ray.getOrigin()[i]) * invRayDir;

        if (tNear > tFar)
            std::swap(tNear, tFar);

        // Ensures robustness in intersection calculation. (Refer PBRT book)
        tFar *= 1.0f + 2.0f * gammaf(3);

        t0 = tNear > t0 ? tNear : t0;
        t1 = tFar < t1 ? tFar : t1;
        if (t0 > t1)
            return false;
    }

    if (enterPoint != nullptr)
        *enterPoint = ray.getPointAt(t0);
    if (exitPoint != nullptr)
        *exitPoint = ray.getPointAt(t1);
    return true;
}

bool AABB::intersectWithRay(const Ray &ray) const {
    // Faster version of ray-box intersection. Checks the entire ray
    // intersection, even in negative direction.
    // Refer: Section 3.1.2, PBRT 3rd Edition, by Matt Pharr

    const glm::vec3 &rayOrigin = ray.getOrigin();
    const glm::vec3 invRayDir = 1.0f / ray.getDirection();
    const int dirIsNegative[3] = {invRayDir[0] < 0.0f, invRayDir[1] < 0.0f,
                                  invRayDir[2] < 0.0f};

    glm::vec3 val = dirIsNegative[0] == 0 ? m_min : m_max;
    float tMin = (val[0] - rayOrigin[0]) * invRayDir[0];
    val = 1 - dirIsNegative[0] == 0 ? m_min : m_max;
    float tMax = (val[0] - rayOrigin[0]) * invRayDir[0];

    val = dirIsNegative[1] == 0 ? m_min : m_max;
    float tYMin = (val[1] - rayOrigin[1]) * invRayDir[1];
    val = 1 - dirIsNegative[1] == 0 ? m_min : m_max;
    float tYMax = (val[1] - rayOrigin[1]) * invRayDir[1];

    // Ensures robustness in intersection calculation. (Refer PBRT book)
    tMax *= 1.0f + 2.0f * gammaf(3);
    tYMax *= 1.0f + 2.0f * gammaf(3);

    if (tMin > tYMax || tYMin > tMax)
        return false;
    if (tYMin > tMin)
        tMin = tYMin;
    if (tYMax < tMax)
        tMax = tYMax;

    val = dirIsNegative[2] == 0 ? m_min : m_max;
    float tZMin = (val[2] - rayOrigin[2]) * invRayDir[2];
    val = 1 - dirIsNegative[2] == 0 ? m_min : m_max;
    float tZMax = (val[2] - rayOrigin[2]) * invRayDir[2];

    // Ensures robustness in intersection calculation. (Refer PBRT book)
    tZMax *= 1.0f + 2.0f * gammaf(3);

    if (tMin > tZMax || tZMin > tMax)
        return false;
    if (tZMin > tMin)
        tMin = tZMin;
    if (tZMax < tMax)
        tMax = tZMax;

    return (tMin < ray.getMaxDistance()) && (tMax > 0);
}

bool AABB::overlaps(const AABB &lhs, const AABB &rhs) {
    const bool x =
            (lhs.m_max[0] >= rhs.m_min[0]) && (lhs.m_min[0] <= rhs.m_max[0]);
    const bool y =
            (lhs.m_max[1] >= rhs.m_min[1]) && (lhs.m_min[1] <= rhs.m_max[1]);
    const bool z =
            (lhs.m_max[2] >= rhs.m_min[2]) && (lhs.m_min[2] <= rhs.m_max[2]);
    return x && y && z;
}

AABB AABB::intersect(const AABB &lhs,
                     const AABB &rhs) {
    return AABB(glm::vec3(std::fmax(lhs.m_min[0], rhs.m_min[0]),
                          std::fmax(lhs.m_min[1], rhs.m_min[1]),
                          std::fmax(lhs.m_min[2], rhs.m_min[2])),
                glm::vec3(std::fmin(lhs.m_max[0], rhs.m_max[0]),
                          std::fmin(lhs.m_max[1], rhs.m_max[1]),
                          std::fmin(lhs.m_max[2], rhs.m_max[2])));
}