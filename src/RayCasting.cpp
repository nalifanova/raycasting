#include "RayCasting.hpp"

#include <algorithm>
#include <set>

#include "Data.hpp"
#include "Physics.hpp"


sf::ConvexShape createPolygon(const size_t verteces)
{
    sf::ConvexShape polygon;
    polygon.setPointCount(verteces);
    polygon.setFillColor(sf::Color::Black);
    polygon.setOutlineColor(sf::Color::White);
    polygon.setOutlineThickness(1.0f);
    return polygon;
}

void castRaysFromCenter1(sf::CircleShape& point, sf::RenderWindow& window)
{
    // Option 1: heavy
    auto center = Vec2(point.getPosition().x, point.getPosition().y);
    auto pointsVec = Data::points;

    std::vector<sf::Vertex> triangleFan;
    triangleFan.emplace_back(sf::Vector2f(center.x, center.y), sf::Color(252, 241, 134));

    // Draw polygon
    for (auto& points: pointsVec)
    {
        auto polygon = createPolygon(points.size());
        polygon.setFillColor(sf::Color(0, 0, 0, 0));

        for (size_t i = 0; i < points.size(); ++i)
        {
            polygon.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
        }
        window.draw(polygon);
    }

    // Ray Casting
    for (float angle = 0; angle <= 360; angle += 0.5f)
    {
        const float radian = angle * 3.14159f / 180.0f;
        Vec2 rayDirection = {std::cos(radian), std::sin(radian)};
        Vec2 rayEnd = center + rayDirection * 1000.0f; // radius = 1000
        auto closest = rayEnd;

        for (auto points: pointsVec)
        {
            // Check intersection with each polygon
            for (size_t i = 0; i < points.size(); ++i)
            {
                Vec2 start = points[i];
                Vec2 end = points[(i + 1) % points.size()];

                const auto intersect = Physics::lineIntersect(center, rayEnd, start, end);
                if (intersect.result)
                {
                    if (center.dist(intersect.pos) < center.dist(closest))
                    {
                        closest = intersect.pos;
                    }
                }
            }
        }
        triangleFan.emplace_back(sf::Vector2f(closest.x, closest.y), sf::Color(252, 241, 134, 255));
    }
    window.draw(&triangleFan[0], triangleFan.size(), sf::TriangleFan);
}

void castRaysFromCenter2(sf::CircleShape& point, sf::RenderWindow& window)
{
    std::vector<Intersection> intersects;
    auto mouse = Vec2(point.getPosition().x, point.getPosition().y);
    auto segments = Data::segments;

    std::set<Vec2> uniquePoints;
    for (auto& vec: segments)
    {
        uniquePoints.insert(vec.a);
        uniquePoints.insert(vec.b);
    }

    std::vector<float> uniqueAngles;
    for (const auto& point: uniquePoints)
    {
        float angle = std::atan2(point.y - mouse.y, point.x - mouse.x);
        uniqueAngles.push_back(angle - 0.00001f);
        uniqueAngles.push_back(angle);
        uniqueAngles.push_back(angle + 0.00001f);
    }

    for (float angle: uniqueAngles)
    {
        Vec2 dir(std::cos(angle), std::sin(angle));
        Ray ray{mouse, mouse + dir * 1000.0f};

        Intersection closestIntersect{false, Vec2(), 0, 0};
        for (const auto& seg: segments)
        {
            Intersection intersect = Physics::getIntersection(ray, seg);
            if (intersect.exists && (!closestIntersect.exists || intersect.param < closestIntersect.param))
            {
                closestIntersect = intersect;
            }
        }

        if (!closestIntersect.exists) { continue; }

        // Add angle and push closest to list of intersects
        closestIntersect.angle = angle;
        intersects.push_back(closestIntersect);
    }

    std::sort(intersects.begin(), intersects.end(), [](const Intersection& a, const Intersection& b)
    {
        return a.angle < b.angle;
    });

    sf::ConvexShape polygon;
    polygon.setPointCount(intersects.size());
    polygon.setFillColor(sf::Color(221, 56, 56, 128));

    for (size_t i = 0; i < intersects.size(); ++i)
    {
        polygon.setPoint(i, sf::Vector2f(intersects[i].point.x, intersects[i].point.y));
    }
    window.draw(polygon);

    for (const auto& seg: segments)
    {
        sf::Vertex line[] = {
            sf::Vertex(sf::Vector2f(seg.a.x, seg.a.y), sf::Color::White)
          , sf::Vertex(sf::Vector2f(seg.b.x, seg.b.y), sf::Color::White)
        };
        window.draw(line, 2, sf::Lines);
    }
}

void castRaysFromCenter3(sf::CircleShape& point, sf::RenderWindow& window)
{
    // Option 3: like option1 but less rays
    const float rayLength = 1000.0f;
    auto center = Vec2(point.getPosition().x, point.getPosition().y);
    const auto pointsVec = Data::points;
    std::vector<sf::Vertex> rays;

    for (float angle = 0; angle <= 360; angle += 25.0f)
    {
        const float radian = angle * 3.14159f / 180.0f;
        Vec2 rayDirection = {std::cos(radian), std::sin(radian)};
        Vec2 rayEnd = center + rayDirection * rayLength;
        auto closest = rayEnd;

        for (const auto& points: pointsVec)
        {
            for (size_t i = 0; i < points.size(); ++i)
            {
                Vec2 start = points[i];
                Vec2 end = points[(i + 1) % points.size()];

                auto intersection = Physics::lineIntersect(center, rayEnd, start, end);
                if (intersection.result)
                {
                    if (center.dist(intersection.pos) < center.dist(closest))
                    {
                        closest = intersection.pos;
                    }
                }
            }
        }
        rays.push_back(sf::Vertex(sf::Vector2f(center.x, center.y), sf::Color(255, 0, 0, 200)));
        rays.push_back(sf::Vertex(sf::Vector2f(closest.x, closest.y), sf::Color(255, 255, 0, 76)));
    }

    // Draw polygon
    for (auto& points: pointsVec)
    {
        auto polygon = createPolygon(points.size());

        for (size_t i = 0; i < points.size(); ++i)
        {
            polygon.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
        }
        window.draw(polygon);
    }

    // Draw rays
    window.draw(&rays[0], rays.size(), sf::Lines);
}
