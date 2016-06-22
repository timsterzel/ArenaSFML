#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP
#include <SFML/Graphics.hpp>
#include "Collision/CollisionCircle.hpp"
#include "Collision/CollisionRect.hpp"
#include "Components/SceneNode.hpp"
#include <vector>


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
};

#endif // COLLISIONHANDLER_HPP
