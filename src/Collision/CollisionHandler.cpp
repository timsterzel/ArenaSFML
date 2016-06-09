#include "Collision/CollisionHandler.hpp"
/*
CollisionHandler::CollisionHandler(SceneNode *sceneGraph)
: m_sceneGraph(sceneGraph)
{

}
*/

bool CollisionHandler::isColliding(const CollisionCircle &objA, const CollisionCircle &objB)
{
    return false;
}

bool CollisionHandler::isColliding(const CollisionRect &objA, const CollisionRect &objB)
{
    return false;
}

bool CollisionHandler::isColliding(const CollisionCircle &objA, const CollisionRect &objB)
{
    return false;
}

bool CollisionHandler::isColliding(const CollisionRect &objA, const CollisionCircle &objB)
{
    return false;
}
