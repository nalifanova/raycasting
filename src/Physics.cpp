#include "Physics.hpp"

Intersect Physics::lineIntersect(const Vec2& a, const Vec2& b, const Vec2& c, const Vec2& d)
{
    const Vec2 r = b - a; // vector r
    const Vec2 s = d - c; // vector s
    const float rxs = r.cross2d(s); // 2d cross product
    const Vec2 cma = c - a;
    const float t = cma.cross2d(s) / rxs; // scalar value for r
    const float u = cma.cross2d(r) / rxs; // scalar value for s

    if (t >= 0 && t <= 1 && u >= 0 && u <= 1)
        return {true, a + r * t};

    return {false, Vec2(0.0f, 0.0f)};
}

Intersection Physics::getIntersection(const Ray& ray, const Segment& segment)
{
    Vec2 r_px = ray.a;
    Vec2 r_dx = ray.b - ray.a;

    Vec2 s_px = segment.a;
    Vec2 s_dx = segment.b - segment.a;

    float r_mag = r_dx.magnitude();
    float s_mag = s_dx.magnitude();

    if (r_dx.x / r_mag == s_dx.x / s_mag && r_dx.y / r_mag == s_dx.y / s_mag)
    {
        return {false, Vec2(), 0};
    }

    float T2 = (r_dx.x * (s_px.y - r_px.y) + r_dx.y * (r_px.x - s_px.x)) / (s_dx.x * r_dx.y - s_dx.y * r_dx.x);
    float T1 = (s_px.x + s_dx.x * T2 - r_px.x) / r_dx.x;

    if (T1 < 0 || T2 < 0 || T2 > 1)
    {
        return {false, Vec2(), 0};
    }

    return {true, Vec2(r_px.x + r_dx.x * T1, r_px.y + r_dx.y * T1), T1};
}
