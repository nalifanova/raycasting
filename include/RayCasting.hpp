#ifndef RAYCASTING_HPP
#define RAYCASTING_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Physics.hpp"
#include "Vec2.hpp"

std::vector<Segment> getSegments();
std::vector<std::vector<Vec2>> getPoints();
std::vector<Vec2> visiblePoints(const std::vector<Vec2>& points, const Vec2& referencePoint, Vec2& lm, Vec2& rm);
Intersection getIntersection(const Ray& ray, const Segment& segment);
sf::ConvexShape createPolygon(size_t verteces);
void castRaysFromCenter1(sf::CircleShape& point, sf::RenderWindow& window);
void castRaysFromCenter2(sf::CircleShape& point, sf::RenderWindow& window);
void castRaysFromCenter3(sf::CircleShape& point, sf::RenderWindow& window);

#endif //RAYCASTING_HPP
