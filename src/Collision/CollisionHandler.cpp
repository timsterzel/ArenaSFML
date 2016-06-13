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
    return dist <= objA.getRadius() || dist <= objB.getRadius();
}

bool CollisionHandler::isColliding(const CollisionRect &objA, const CollisionRect &objB)
{
    std::cout << "isColliding CollisionRect, CollisionRect" << std::endl;
    return false;
}

// http://yal.cc/rectangle-circle-intersection-test/
/*
bool CollisionHandler::isColliding(const CollisionCircle &objA, const CollisionRect &objB)
{
    // To do: translate the rect so there is no rotation
    float rotation = objB.getRotation();


    //std::cout << "isColliding CollisionCircle, CollisionRect" << std::endl;
    //const sf::Vector2f CirclePos = { objA.getWorldPosition() };
    //const sf::Vector2f RectPos = { Calc::rotatePointAround(objB.getWorldPosition(), objA.getWorldPosition(), -rotation) };

    const sf::Vector2f CirclePos = { objA.getWorldPosition() };
    const sf::Vector2f RectPos = { objB.getWorldPosition() };


    const float RectWidth = { objB.getWidth() };
    const float RectHeight = { objB.getHeight() };

    // Get the nearest point on the rectangnle to the circle
    const float NearestX = { std::max(RectPos.x, std::min(CirclePos.x, RectPos.x + RectWidth)) };
    const float NearestY = { std::max(RectPos.y, std::min(CirclePos.y, RectPos.y + RectHeight)) };
    // Get the distance between the nearest positions on the rect and cirtcles position
    const float distX = CirclePos.x - NearestX;
    const float distY = CirclePos.y - NearestY;
    const float dist = std::sqrt((distX * distX)  + (distY * distY));
    // check if the distance is smaller or equals the distance (then there is a collision)
    return dist <= objA.getRadius();
}
*/
bool CollisionHandler::isColliding(const CollisionCircle &objA, const CollisionRect &objB)
{
    // To do: translate the rect so there is no rotation
    float rotation = objB.getRotation();


    //std::cout << "isColliding CollisionCircle, CollisionRect" << std::endl;
    //const sf::Vector2f CirclePos = { objA.getWorldPosition() };
    //const sf::Vector2f RectPos = { Calc::rotatePointAround(objB.getWorldPosition(), objA.getWorldPosition(), -rotation) };

    const sf::Vector2f CirclePos = { objA.getWorldPosition() };
    const sf::Vector2f RectPos = { objB.getWorldPosition() };


    const float RectWidth = { objB.getWidth() };
    const float RectHeight = { objB.getHeight() };

    // Get the nearest point on the rectangnle to the circle
    const float NearestX = { std::max(RectPos.x - RectWidth / 2.f, std::min(CirclePos.x, RectPos.x + RectWidth / 2.f)) };
    const float NearestY = { std::max(RectPos.y - RectHeight / 2.f, std::min(CirclePos.y, RectPos.y + RectHeight / 2.f)) };
    // Get the distance between the nearest positions on the rect and cirtcles position
    const float distX = CirclePos.x - NearestX;
    const float distY = CirclePos.y - NearestY;
    const float dist = std::sqrt((distX * distX)  + (distY * distY));
    // check if the distance is smaller or equals the distance (then there is a collision)
    return dist <= objA.getRadius();
}


bool CollisionHandler::isColliding(const CollisionRect &objA, const CollisionCircle &objB)
{
    //std::cout << "isColliding CollisionRect, CollisionCircle" << std::endl;
    CollisionHandler::isColliding(objB, objA);
    return false;
}
