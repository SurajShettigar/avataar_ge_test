#ifndef MATERIAL_TEST_AABB_HPP
#define MATERIAL_TEST_AABB_HPP

#include <glm/vec3.hpp>

class Ray {
private:
    glm::vec3 m_origin;
    glm::vec3 m_direction;
    mutable float m_tMax;
public:
    Ray(const glm::vec3 &origin, const glm::vec3 &direction,
        float maxDistance = std::numeric_limits<float>::max())
            : m_origin{origin}, m_direction{direction}, m_tMax{maxDistance} {};
    ~Ray() = default;

    Ray(const Ray &ray)
    {
        if (this != &ray)
        {
            m_origin = ray.m_origin;
            m_direction = ray.m_direction;
            m_tMax = ray.m_tMax;
        }
    }

    bool operator==(const Ray &rhs)
    {
        return m_origin == rhs.m_origin && m_direction == rhs.m_direction;
    }
    bool operator!=(const Ray &rhs)
    {
        return !(*this == rhs);
    }

    // Getters-Setters
    inline glm::vec3 getOrigin() const
    {
        return m_origin;
    }

    inline glm::vec3 getDirection() const
    {
        return m_direction;
    }

    inline float getMaxDistance() const
    {
        return m_tMax;
    }

    inline void setMaxDistance(float max) const
    {
        m_tMax = max;
    }

    inline glm::vec3 getPointAt(float t) const
    {
        return m_origin + t * m_direction;
    }

    glm::vec3 operator()(float t) const
    {
        return getPointAt(t);
    }
};

class AABB {
public:
    AABB();
    explicit AABB(const glm::vec3 &point);

    explicit AABB(const glm::vec3 &min, const glm::vec3 &max);

    ~AABB() = default;

    bool operator==(const AABB &rhs) const;

    bool operator!=(const AABB &rhs) const;

    // Getters-Setters
    [[nodiscard]] inline glm::vec3 getMin() const {
        return m_min;
    }

    [[nodiscard]] inline glm::vec3 getMax() const {
        return m_max;
    }

    [[nodiscard]] inline glm::vec3 getCenter() const {
        return (m_min + m_max) * 0.5f;
    }

    [[nodiscard]] inline glm::vec3 getSize() const {
        return (m_max - m_min);
    }

    [[nodiscard]] inline glm::vec3 getExtent() const {
        return getSize() * 0.5f;
    }

    void encapsulate(const glm::vec3 &point);

    void encapsulate(const AABB &bounds);

    void expand(float delta);

    [[nodiscard]] bool contains(const glm::vec3 &point) const;

    bool intersectWithRay(const Ray &ray, glm::vec3 *enterPoint,
                          glm::vec3 *exitPoint) const;

    [[nodiscard]] bool intersectWithRay(const Ray &ray) const;

    inline static AABB createFromCenterSize(const glm::vec3 &center,
                                               const glm::vec3 &size) {
        return AABB(center - size * 0.5f, center + size * 0.5f);
    }

    static bool overlaps(const AABB &lhs, const AABB &rhs);

    static AABB intersect(const AABB &lhs, const AABB &rhs);

private:
    glm::vec3 m_min{1.0f};
    glm::vec3 m_max{0.0f};
};


#endif //MATERIAL_TEST_AABB_HPP
