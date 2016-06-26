#include "Collision/CollisionHandler.hpp"
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Calc.hpp"
/*
CollisionHandler::CollisionHandler(SceneNode *sceneGraph)
: m_sceneGraph(sceneGraph)
{

}
*/

CollisionInfo CollisionHandler::isColliding(CollisionCircle &objA, CollisionCircle &objB)
{
    //std::cout << "isColliding CollisionCircle, CollisionCircle" << std::endl;
    //std::cout << "objA Pos: x = " << objA.getWorldPosition().x << " y = " << objA.getWorldPosition().y << std::endl;
    //std::cout << "objB Pos: x = " << objB.getWorldPosition().x << " y = " << objB.getWorldPosition().y << std::endl;
    const float distX = { objA.getWorldPosition().x - objB.getWorldPosition().x };
    const float distY = { objA.getWorldPosition().y - objB.getWorldPosition().y };
    const float dist = std::sqrt((distX * distX)  + (distY * distY));
    bool isCollision = { dist < objA.getRadius() + objB.getRadius() };
    return CollisionInfo(isCollision);
}

// GJK algorithm
/*
bool CollisionHandler::isColliding(CollisionRect &objA, CollisionRect &objB)
{

    std::cout << "isColliding CollisionRect, CollisionRect" << std::endl;
    // Choose any vector (Its n ot relevant which vector)
    sf::Vector2f dir(1.f, 1.f);
    objA.computeVertices();
    objB.computeVertices();

    std::vector<sf::Vector2f> simplex;
    // Get and store first minkowski difference point
    sf::Vector2f p = { support(objA, objB, dir) };
    simplex.push_back(p);
    // negate the direction
    //dir = -dir;
    // Now we change the search direction. Now we have a search direction from the new point to the origin (P0 = 0 - P = -P)
    //
    dir = -p;
    while (true)
    {
        // Get another minkowski difference point (Its another because we now use the negated direction
        simplex.push_back({ support(objA, objB, dir) });
        sf::Vector2f lastPoint = simplex.back();
        // If we have as the search direction the last point to the origin and the dot product between this search direction and the new point
        // we get with this is under 0 it means that the angle between the seach direction and the new poit (as vector) is over 90 degrees.
        // if this is the case, the shape cannot contain the origin, because we have the farthest point to this direction which dont have pass the origin
        // (You can see it when you draw it)
        if (Calc::getVec2Scalar<sf::Vector2f, sf::Vector2f>(lastPoint, dir) < 0)
        {
            return false;
        }
        else
        {
            if (containsOrigin(simplex, dir))
            {
                return true;
            }
        }
    }
    return false;
}
*/




// SAT algorithm
CollisionInfo CollisionHandler::isColliding(CollisionRect &objA, CollisionRect &objB)
{
    objA.computeVertices();
    objB.computeVertices();
    std::vector<sf::Vector2f> verticesA = { objA.getVertices() };
    std::vector<sf::Vector2f> verticesB = { objB.getVertices() };
    // Store the axises to test
    std::vector<sf::Vector2f> axisesA = { getAxises(verticesA) };
    std::vector<sf::Vector2f> axisesB = { getAxises(verticesB) };

    for (sf::Vector2f axis : axisesA)
    {
        //std::cout << "AxisA: x: " << axis.x << " y: " << axis.y << std::endl;
        //std::cout << "ProjectionA min: " << getProjection(axis, verticesA).first << " max: " << getProjection(axis, verticesA).second
        //<< " B : min: " << getProjection(axis, verticesB).first << " max: " << getProjection(axis, verticesB).second << std::endl;
        if (!areAxisProjectionsIntersecting(getProjection(axis, verticesA), getProjection(axis, verticesB)))
        {
            return CollisionInfo(false);
        }
    }
    for (sf::Vector2f axis : axisesB)
    {
        //std::cout << "AxisB: x: " << axis.x << " y: " << axis.y << std::endl;
        //std::cout << "ProjectionA min: " << getProjection(axis, verticesA).first << " max: " << getProjection(axis, verticesA).second
        //<< " B : min: " << getProjection(axis, verticesB).first << " max: " << getProjection(axis, verticesB).second << std::endl;
        if (!areAxisProjectionsIntersecting(getProjection(axis, verticesA), getProjection(axis, verticesB)))
        {
            return CollisionInfo(false);
        }
    }
    // If we were not able to create a seperate axis between the two shapes after testing all axis there have to be an intersection
    return CollisionInfo(true);
}

std::pair<float, float> CollisionHandler::getProjection(sf::Vector2f axis, const std::vector<sf::Vector2f> &vertices)
{
    float minSkalar = Calc::getVec2Scalar<sf::Vector2f, sf::Vector2f>(axis, vertices[0]);
    float maxSkalar = minSkalar;
    for (std::size_t i = 1; i != vertices.size(); i++)
    {
        float skalar = Calc::getVec2Scalar<sf::Vector2f, sf::Vector2f>(axis, vertices[i]);
        if (skalar < minSkalar)
        {
            minSkalar = skalar;
        }
        else if (skalar > maxSkalar)
        {
            maxSkalar = skalar;
        }
    }
    return { minSkalar, maxSkalar };
}

std::vector<sf::Vector2f> CollisionHandler::getAxises(const std::vector<sf::Vector2f> &Vertices)
{
    std::vector<sf::Vector2f> axises;
    const std::size_t VerticesSize = Vertices.size();
    for (std::size_t i = 0; i != VerticesSize; i++)
    {
        sf::Vector2f edge;
        if (i != 0)
        {
            edge = Vertices[i] - Vertices[i - 1];
        }
        else
        {
            edge = Vertices[0] - Vertices[VerticesSize - 1];
        }
        sf::Vector2f perp = { Calc::getVec2PerpendicularLeft<sf::Vector2f>(edge) };
        // Get normalized vector
        perp = Calc::normalizeVec2<sf::Vector2f>(perp);
        axises.push_back(perp);
    }
    return axises;
}

bool CollisionHandler::areAxisProjectionsIntersecting(const std::pair<float, float> ProjectionA, const std::pair<float, float> ProjectionB)
{
    const float MinA = { ProjectionA.first };
    const float MaxA = { ProjectionA.second };
    const float MinB = { ProjectionB.first };
    const float MaxB = { ProjectionA.second };
    // Check if the projections are intersecting, when not the shapes qare not colliding
    // because we can seperate the two shapes
    if ( (MinA < MaxB && MaxA < MinB) || (MinB < MaxA && MaxB < MinA) )
    {
        return false;
    }
    return true;
}

CollisionInfo CollisionHandler::isColliding(CollisionCircle &objA, CollisionRect &objB)
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
    bool isCollision = { NearestCircleDistance < objA.getRadius() };
    return CollisionInfo(isCollision);
}


CollisionInfo CollisionHandler::isColliding(CollisionRect &objA, CollisionCircle &objB)
{
    return CollisionHandler::isColliding(objB, objA);;
}

sf::Vector2f CollisionHandler::support(CollisionRect &objA, CollisionRect &objB, sf::Vector2f dir)
{
    // Get the vertex of the first rect which is the nearest to the direction vector
    sf::Vector2f SupportVecA = objA.getFarthestPointInDirection(dir);
    // Get the vertex of the second rect which is the nearest to the opposite direction vector
    sf::Vector2f SupportVecB = objB.getFarthestPointInDirection(-dir);

    return SupportVecA - SupportVecB;
}

bool CollisionHandler::containsOrigin(std::vector<sf::Vector2f> &simpex, sf::Vector2f &dir)
{
    sf::Vector2f a = simpex.back();
    sf::Vector2f ao = -a;
    if (simpex.size() == 3)
    {
        // The simplex is a triangle
        sf::Vector2f b = simpex[1];
        sf::Vector2f c = simpex.front();
        sf::Vector2f ab = b - a;
        sf::Vector2f ac = c - a;
        // Get the normals
        sf::Vector2f abPerp = Calc::getVec2TripleProduct<sf::Vector2f, sf::Vector2f, sf::Vector2f>(ac, ab, ab);
        sf::Vector2f acPerp = Calc::getVec2TripleProduct<sf::Vector2f, sf::Vector2f, sf::Vector2f>(ab, ac, ac);
        if (Calc::getVec2Scalar<sf::Vector2f, sf::Vector2f>(abPerp, ao) > 0)
        {
            // Remove point c
            simpex.erase(simpex.begin() + 0);
            // New direction is abPerp
            dir = abPerp;
        }
        else
        {
            if (Calc::getVec2Scalar<sf::Vector2f, sf::Vector2f>(acPerp, ao) > 0)
            {
                // Remove point b
                simpex.erase(simpex.begin() + 1);
                dir = acPerp;
            }
            else
            {
                return true;
            }
        }
    }
    else
    {
        // The simplex is a line
        sf::Vector2f b = simpex.front();
        sf::Vector2f ab = b - a;
        // Get perpendicular vector of ab to the origin (Vector which is 90 degrees to the ab vector)
        sf::Vector2f abPerp = Calc::getVec2TripleProduct<sf::Vector2f, sf::Vector2f, sf::Vector2f>(ab, ao, ab);
        dir = abPerp;
    }
    return false;
}

