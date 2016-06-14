#include "Collision/CollisionHandler.hpp"
#include <iostream>
#include <cmath>
#include <algorithm>
#include "Calc.hpp"
/*
CollisionHandler::CollisionHandler(SceneNode *sceneGraph)
: m_sceneGraph(sceneGraph)
{

}
*/

bool CollisionHandler::isColliding(const CollisionCircle &objA, const CollisionCircle &objB)
{
    //std::cout << "isColliding CollisionCircle, CollisionCircle" << std::endl;
    //std::cout << "objA Pos: x = " << objA.getWorldPosition().x << " y = " << objA.getWorldPosition().y << std::endl;
    //std::cout << "objB Pos: x = " << objB.getWorldPosition().x << " y = " << objB.getWorldPosition().y << std::endl;
    const float distX = { objA.getWorldPosition().x - objB.getWorldPosition().x };
    const float distY = { objA.getWorldPosition().y - objB.getWorldPosition().y };
    const float dist = std::sqrt((distX * distX)  + (distY * distY));
    return dist < objA.getRadius() + objB.getRadius();
}

bool CollisionHandler::isColliding(const CollisionRect &objA, const CollisionRect &objB)
{
    std::cout << "isColliding CollisionRect, CollisionRect" << std::endl;
    return false;
}

bool CollisionHandler::isColliding(const CollisionCircle &objA, const CollisionRect &objB)
{
    const float RectRotation = objB.getWorldRotation();
    // We use a local coordinate system, where the Rect is axis aligned at (0|0)
    const sf::Vector2f RectPos{ 0.f, 0.f };
    // The Circle have to get translated into this local coordinate system. Because the rect can have a rotation we must translate the rotate of the circle, too.
    // (Here RectRotation is used instean of RectRotation, because Calc::rotatePointAround() use the behavior of the coordinate system)
    const sf::Vector2f CirclePos = { Calc::rotatePointAround(objA.getWorldPosition() - objB.getWorldPosition(), { 0.f, 0.f }, RectRotation) };

    const float RectWidth = { objB.getWidth() };
    const float RectHeight = { objB.getHeight() };
    // Get the vector which represents the vector of the distance between the position of the rect and circle
    const sf::Vector2f CircleRectDistVec = { CirclePos.x - RectPos.x, CirclePos.y - RectPos.y };
    // Determine the nearest position on the rect to the circle (Here we can use clamping for that)
    const float NearestX = { Calc::clamp(CircleRectDistVec.x, -(RectWidth / 2.f), RectWidth / 2.f) };
    const float NearestY = { Calc::clamp(CircleRectDistVec.y, -(RectHeight / 2.f), RectHeight / 2.f) };
    const sf::Vector2f Nearest{ RectPos.x + NearestX,  RectPos.y + NearestY };
    // Get the distance between the nearest point on rect to the circle and the circle
    const float NearestCircleDistance = { Calc::getVec2Length<sf::Vector2f>(Nearest - CirclePos) };
    // When the distance beetween the nearest point on circle and circles position
    // is smaller than the radius of the circle we have a collison
    return NearestCircleDistance < objA.getRadius();
}


bool CollisionHandler::isColliding(const CollisionRect &objA, const CollisionCircle &objB)
{
    return CollisionHandler::isColliding(objB, objA);;
}

