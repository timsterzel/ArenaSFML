#ifndef COLLISIONHANDLER_HPP
#define COLLISIONHANDLER_HPP
#include <SFML/Graphics.hpp>
#include "Collision/CollisionCircle.hpp"
#include "Components/SceneNode.hpp"


class CollisionHandler
{
    private:
        //SceneNode *m_sceneGraph;
    public:
        //explicit CollisionHandler(SceneNode *sceneGraph);
        static bool isColliding(const CollisionCircle &objA, const CollisionCircle &objB);

};

#endif // COLLISIONHANDLER_HPP
