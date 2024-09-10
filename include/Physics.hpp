#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include "Vec2.hpp"

struct Intersect
{
    bool result = false;
    Vec2 pos;
    float angle = 0.0f;
};

struct Segment
{
    Vec2 a, b;
};

struct Intersection
{
    bool exists{};
    Vec2 point;
    float param{};
    float angle{};
};

struct Ray
{
    Vec2 a, b;
};

class Physics
{
public:
    static Intersect lineIntersect(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d);

    /**
     * source: https://ncase.me/sight-and-light/
     */
    static Intersection getIntersection(const Ray& ray, const Segment& segment);
};

#endif //PHYSICS_HPP
