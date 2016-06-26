#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP
#include <SFML/Graphics.hpp>
#include "Collision/CollisionCircle.hpp"
#include "Collision/CollisionRect.hpp"
#include "Components/SceneNode.hpp"
#include <vector>
#include <utility>


class CollisionHandler
{
    private:
        //SceneNode *m_sceneGraph;
    public:

        //explicit CollisionHandler(SceneNode *sceneGraph);
        static bool isColliding(CollisionCircle &objA, CollisionCircle &objB);
        static bool isColliding(CollisionRect &objA, CollisionRect &objB);
        static bool isColliding(CollisionCircle &objA, CollisionRect &objB);
        static bool isColliding(CollisionRect &objA, CollisionCircle &objB);

    private:
        // Support function to get a point for a specific direction from a convex shape
        static sf::Vector2f support(CollisionRect &objA, CollisionRect &objB, sf::Vector2f dir);
        static bool containsOrigin(std::vector<sf::Vector2f> &simpex, sf::Vector2f &dir);

        // For SAT
        static std::pair<float, float> getProjection(sf::Vector2f axis, const std::vector<sf::Vector2f> &Vertices);
        // Return the perpendicular, normalized vectors to edges of the shape, represented through its vertices.
        // The vertices have to be in the right order, so they create the needed shape by iterating over it
        static std::vector<sf::Vector2f> getAxises(const std::vector<sf::Vector2f> &Vertices);
        static bool areAxisProjectionsIntersecting(const std::pair<float, float> ProjectionA, const std::pair<float, float> ProjectionB);
};

#endif // COLLISIONHANDLER_HPP
