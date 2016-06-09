#include "Collision/CollisionHandler.hpp"
#include <iostream>
#include <cmath>
/*
CollisionHandler::CollisionHandler(SceneNode *sceneGraph)
: m_sceneGraph(sceneGraph)
{

}
*/

bool CollisionHandler::isColliding(const CollisionCircle &objA, const CollisionCircle &objB)
{
    std::cout << "isColliding CollisionCircle, CollisionCircle" << std::endl;
    std::cout << "objA Pos: x = " << objA.getWorldPosition().x << " y = " << objA.getWorldPosition().y << std::endl;
    std::cout << "objB Pos: x = " << objB.getWorldPosition().x << " y = " << objB.getWorldPosition().y << std::endl;
    const float distX = { objA.getWorldPosition().x - objB.getWorldPosition().x };
    const float distY = { objA.getWorldPosition().y - objB.getWorldPosition().y };
    const float dist = std::sqrt((distX * distX)  + (distY * distY));
    return dist <= objA.getRadius() || dist <= objB.getRadius();
}

bool CollisionHandler::isColliding(const CollisionRect &objA, const CollisionRect &objB)
{
    std::cout << "isColliding CollisionRect, CollisionRect" << std::endl;
    return false;
}

bool CollisionHandler::isColliding(const CollisionCircle &objA, const CollisionRect &objB)
{
    std::cout << "isColliding CollisionCircle, CollisionRect" << std::endl;
    return false;
}

bool CollisionHandler::isColliding(const CollisionRect &objA, const CollisionCircle &objB)
{
    std::cout << "isColliding CollisionRect, CollisionCircle" << std::endl;
    return false;
}
