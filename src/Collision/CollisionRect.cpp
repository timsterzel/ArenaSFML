#include "Collision/CollisionRect.hpp"
#include "Collision/CollisionHandler.hpp"
#include "Calc.hpp"

CollisionRect::CollisionRect(sf::Vector2f rectSize, bool *draw)
: CollisionShape(draw)
, m_width{ rectSize.x }
, m_height{ rectSize.y }
{

}

float CollisionRect::getWidth() const
{
    return m_width;
}

float CollisionRect::getHeight() const
{
    return m_height;
}

void CollisionRect::computeVertices()
{
    const float Rotation = { getWorldRotation() };
    const sf::Vector2f Position = { getWorldPosition() };
    //std::cout << "Rotation: " << Rotation << std::endl;
    // Compute the rects vertices as AABB
    const sf::Vector2f EdgeA = { Position.x - m_width / 2.f, Position.y - m_height / 2.f };
    const sf::Vector2f EdgeB = { Position.x + m_width / 2.f, Position.y - m_height / 2.f };
    const sf::Vector2f EdgeC = { Position.x + m_width / 2.f, Position.y + m_height / 2.f };
    const sf::Vector2f EdgeD = { Position.x - m_width / 2.f, Position.y + m_height / 2.f };
    // Apply rects rotation to the vertices
    const sf::Vector2f EdgeAR = { Calc::rotatePointAround(EdgeA, Position, -Rotation) };
    const sf::Vector2f EdgeBR = { Calc::rotatePointAround(EdgeB, Position, -Rotation) };
    const sf::Vector2f EdgeCR = { Calc::rotatePointAround(EdgeC, Position, -Rotation) };
    const sf::Vector2f EdgeDR = { Calc::rotatePointAround(EdgeD, Position, -Rotation) };
    // Add the vertices to the container
    m_vertices.clear();
    // Add vertices clockwise
    m_vertices.push_back(EdgeAR);
    m_vertices.push_back(EdgeBR);
    m_vertices.push_back(EdgeCR);
    m_vertices.push_back(EdgeDR);
}

std::vector<sf::Vector2f> CollisionRect::getVertices() const
{
    return m_vertices;
}

void CollisionRect::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if (*m_draw)
    {
        sf::RectangleShape rect({ m_width, m_height });
        rect.setFillColor(sf::Color(255, 0, 0, 160));
        rect.setOrigin(m_width / 2.f, m_height / 2.f);
        target.draw(rect, states);
    }
}

CollisionInfo CollisionRect::isColliding(CollisionShape &collider)
{
    return collider.isColliding(*this);
}

CollisionInfo CollisionRect::isColliding(CollisionCircle &collider)
{
    return CollisionHandler::isColliding(*this, collider);
}

CollisionInfo CollisionRect::isColliding(CollisionRect &collider)
{
    return CollisionHandler::isColliding(*this, collider);
}

// Return the point which is nearest (farthest) to the given direction
sf::Vector2f CollisionRect::getFarthestPointInDirection(sf::Vector2f dir) const
{
    int maxPos = 0;
    float maxScalar = Calc::getVec2Scalar<sf::Vector2f, sf::Vector2f>(dir, m_vertices[0]);
    // Determine which verices of the rect is the nearest ( have the highest dot product) to the given vector
    for (std::size_t i = 0; i != m_vertices.size(); i++)
    {
        float scalar = { Calc::getVec2Scalar<sf::Vector2f, sf::Vector2f>(dir, m_vertices[i]) };
        if (scalar > maxScalar)
        {
            maxPos = i;
            maxScalar = scalar;
        }
    }
    return m_vertices[maxPos];
}
