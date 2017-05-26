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

CollisionInfo CollisionHandler::isColliding(CollisionCircle &objA, 
        CollisionCircle &objB)
{
    const sf::Vector2f distVec = { objA.getWorldPosition() - objB.getWorldPosition() };
    const float dist = Calc::getVec2Length<sf::Vector2f>(distVec);
    bool isCollision = { dist < objA.getRadius() + objB.getRadius() };
    if (isCollision)
    {
        float overlap = (objA.getRadius() + objB.getRadius()) - dist;
        return CollisionInfo(true, overlap, distVec, -distVec, objA.getParent(), 
                objB.getParent());
    }
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
        simplex.push_back({ supportGJK(objA, objB, dir) });
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
            if (containsOriginGJK(simplex, dir))
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
    std::vector<sf::Vector2f> axisesA = { getAxisesSAT(verticesA) };
    std::vector<sf::Vector2f> axisesB = { getAxisesSAT(verticesB) };
    // Used provide collision information
    // Use as standart an overlapwhich is to high that it cant occur in the game
    float overlap = { 99999.f };
    sf::Vector2f collisionAxis;

    for (sf::Vector2f axis : axisesA)
    {
        const std::pair<float, float> ProjectionA{ 
            getProjectionSAT(axis, verticesA) };
        const std::pair<float, float> ProjectionB{ 
            getProjectionSAT(axis, verticesB) };
        if (!areAxisProjectionsIntersectingSAT(ProjectionA, ProjectionB))
        {
            return CollisionInfo(false);
        }
        else
        {
            float overlapTmp = { getOverlapSAT(ProjectionA, ProjectionB) };
            if (overlapTmp < overlap)
            {
                overlap = overlapTmp;
                collisionAxis = axis;
            }
        }
    }
    for (sf::Vector2f axis : axisesB)
    {
        const std::pair<float, float> ProjectionA{ 
            getProjectionSAT(axis, verticesA) };
        const std::pair<float, float> ProjectionB{ 
            getProjectionSAT(axis, verticesB) };
        if (!areAxisProjectionsIntersectingSAT(ProjectionA, ProjectionB))
        {
            return CollisionInfo(false);
        }
        else
        {
            float overlapTmp = { getOverlapSAT(ProjectionA, ProjectionB) };
            if (overlapTmp < overlap)
            {
                overlap = overlapTmp;
                collisionAxis = axis;
            }
        }
    }
    const sf::Vector2f dirVecAB{ 
        objB.getWorldPosition() - objA.getWorldPosition() };
    sf::Vector2f directionA;
    sf::Vector2f directionB;
    // Angle is bigger then 90 degrees, vectors are not in the same direction.
    // When we have a AB vector (objBs position - objAs position) and AB is not in 
    // the direction of the axis normal, ObjA have to be moves in the direction of 
    // the axis normal and objB int the opposite direction.
    if (Calc::getVec2Scalar<sf::Vector2f, sf::Vector2f>(dirVecAB, collisionAxis) < 0)
    {
        directionA = collisionAxis;
        directionB = -collisionAxis;
    }
    // Angle is smaller then 90 degrees, vectors are in the same direction
    else
    {
        directionA = -collisionAxis;
        directionB = collisionAxis;
    }

    // If we were not able to create a seperate axis between the two shapes after 
    // testing all axis there have to be an intersection
    return CollisionInfo(true, overlap, directionA, directionB, objA.getParent(), 
            objB.getParent());
}

CollisionInfo CollisionHandler::isColliding(CollisionCircle &objA, 
        CollisionRect &objB)
{
    const float RectRotation = objB.getWorldRotation();
    // We use a local coordinate system, where the Rect is axis aligned at (0|0)
    const sf::Vector2f RectPos{ 0.f, 0.f };
    // The Circle have to get translated into this local coordinate system. 
    // Because the rect can have a rotation we must translate the rotate of the 
    // circle, too.(Here RectRotation is used instean of RectRotation, 
    // because Calc::rotatePointAround() use the behavior of the coordinate system)
    const sf::Vector2f CirclePos{ Calc::rotatePointAround(
            objA.getWorldPosition() - objB.getWorldPosition(), { 0.f, 0.f }, 
            RectRotation) };

    const float RectWidth = { objB.getWidth() };
    const float RectHeight = { objB.getHeight() };
    // Get the vector which represents the vector of the distance between the 
    // position of the rect and circle
    const sf::Vector2f CircleRectDistVec{ 
        CirclePos.x - RectPos.x, CirclePos.y - RectPos.y };
    // Determine the nearest position on the rect to the circle 
    // (Here we can use clamping for that)
    const float NearestX{ 
        Calc::clamp(CircleRectDistVec.x, -(RectWidth / 2.f), RectWidth / 2.f) };
    const float NearestY{ 
        Calc::clamp(CircleRectDistVec.y, -(RectHeight / 2.f), RectHeight / 2.f) };
    const sf::Vector2f Nearest = { RectPos.x + NearestX,  RectPos.y + NearestY };
    // Get the distance between the nearest point on rect to the circle and the 
    // circle
    const float NearestCircleDistance{ 
        Calc::getVec2Length<sf::Vector2f>(Nearest - CirclePos) };
    // When the distance beetween the nearest point on circle and circles position
    // is smaller than the radius of the circle we have a collison
    bool isCollision{ NearestCircleDistance < objA.getRadius() };
    if (isCollision)
    {
        // Translate data back to world coordinates
        const sf::Vector2f CirclePosWorld{ objA.getWorldPosition() };
        const sf::Vector2f NearestPosWorld{ 
            Calc::rotatePointAround(Nearest, { 0.f, 0.f }, 
                    -RectRotation) + objB.getWorldPosition() };

        const float Overlap = objA.getRadius() - NearestCircleDistance;
        const sf::Vector2f Direction = CirclePosWorld - NearestPosWorld;
        return CollisionInfo(true, Overlap, Direction, -Direction, objA.getParent(),
                objB.getParent());
    }
    return CollisionInfo(false);
}


CollisionInfo CollisionHandler::isColliding(CollisionRect &objA, CollisionCircle &objB)
{
    return CollisionHandler::isColliding(objB, objA);;
}

// SAT
std::pair<float, float> CollisionHandler::getProjectionSAT(sf::Vector2f axis, 
        const std::vector<sf::Vector2f> &vertices)
{
    float minSkalar = 
        Calc::getVec2Scalar<sf::Vector2f, sf::Vector2f>(axis, vertices[0]);
    float maxSkalar = minSkalar;
    for (std::size_t i = 1; i != vertices.size(); i++)
    {
        float skalar = 
            Calc::getVec2Scalar<sf::Vector2f, sf::Vector2f>(axis, vertices[i]);
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

// SAT
std::vector<sf::Vector2f> CollisionHandler::getAxisesSAT(
        const std::vector<sf::Vector2f> &Vertices)
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
        // If we use the left perpenduclar or right perpendicular depends on the 
        // direction of the edge direction vectors.
        // Here there are created in clockwise, so we have to use the left 
        // perpenduclar, so the normal point outwards
        sf::Vector2f perp = { Calc::getVec2PerpendicularLeft<sf::Vector2f>(edge) };
        // Get normalized vector
        perp = Calc::normalizeVec2<sf::Vector2f>(perp);
        axises.push_back(perp);
    }
    return axises;
}

// SAT
bool CollisionHandler::areAxisProjectionsIntersectingSAT(
        const std::pair<float, float> ProjectionA, 
        const std::pair<float, float> ProjectionB)
{
    const float MinA = { ProjectionA.first };
    const float MaxA = { ProjectionA.second };
    const float MinB = { ProjectionB.first };
    const float MaxB = { ProjectionA.second };
    // Check if the projections are intersecting, when not the shapes qare not 
    // colliding because we can seperate the two shapes
    if ( (MinA < MaxB && MaxA < MinB) || (MinB < MaxA && MaxB < MinA) )
    {
        return false;
    }
    return true;
}

// SAT
float CollisionHandler::getOverlapSAT(const std::pair<float, float> ProjectionA, 
        const std::pair<float, float> ProjectionB)
{
    if (areAxisProjectionsIntersectingSAT(ProjectionA, ProjectionB))
    {
        const float MinA = { ProjectionA.first };
        const float MaxA = { ProjectionA.second };
        const float MinB = { ProjectionB.first };
        const float MaxB = { ProjectionA.second };
        return std::min(MaxA, MaxB) - std::max(MinA, MinB);
    }
    return 0.f;
}

// GJK
sf::Vector2f CollisionHandler::supportGJK(CollisionRect &objA, CollisionRect &objB, sf::Vector2f dir)
{
    // Get the vertex of the first rect which is the nearest to the direction vector
    sf::Vector2f SupportVecA = objA.getFarthestPointInDirection(dir);
    // Get the vertex of the second rect which is the nearest to the opposite 
    // direction vector
    sf::Vector2f SupportVecB = objB.getFarthestPointInDirection(-dir);
    return SupportVecA - SupportVecB;
}

// GJK
bool CollisionHandler::containsOriginGJK(std::vector<sf::Vector2f> &simpex, sf::Vector2f &dir)
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
        sf::Vector2f abPerp = 
            Calc::getVec2TripleProduct<sf::Vector2f, sf::Vector2f, sf::Vector2f>(
                    ac, ab, ab);
        sf::Vector2f acPerp = 
            Calc::getVec2TripleProduct<sf::Vector2f, sf::Vector2f, sf::Vector2f>(
                    ab, ac, ac);
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
        // Get perpendicular vector of ab to the origin 
        // (Vector which is 90 degrees to the ab vector)
        sf::Vector2f abPerp = 
            Calc::getVec2TripleProduct<sf::Vector2f, sf::Vector2f, sf::Vector2f>(
                    ab, ao, ab);
        dir = abPerp;
    }
    return false;
}

