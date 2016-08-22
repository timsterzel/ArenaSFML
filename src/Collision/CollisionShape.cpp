#include "Collision/CollisionShape.hpp"

CollisionShape::CollisionShape()
: m_parent{ nullptr }
, m_draw{ false }
{

}

sf::Transform CollisionShape::getWorldTransform() const
{
    sf::Transform trform = getTransform();
    if (m_parent != nullptr)
    {
        trform = m_parent->getWorldTransform() * trform;
    }
    return trform;
}

sf::Vector2f CollisionShape::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

void CollisionShape::setParent(SceneNode *parent)
{
    m_parent = parent;
}

SceneNode* CollisionShape::getParent() const
{
    return m_parent;
}

void CollisionShape::setDraw(const bool draw)
{
    m_draw = draw;
}

bool CollisionShape::getDraw() const
{
    return m_draw;
}


float CollisionShape::getWorldRotation() const
{
    float rotation = { getRotation() };
    if (m_parent != nullptr)
    {
        rotation += m_parent->getWorldRotation();
    }
    return rotation;
}
/*
void Collision::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // Do nothing by default
}

bool Collision::isColliding(const Collision &collider) const
{
    // No Collision specified, return false
    return false;
}

bool Collision::isColliding(const CollisionCircle &collider) const
{
    // No Collision specified, return false
    return false;
}

bool Collision::isColliding(const CollisionRect &collider) const
{
    // No Collision specified, return false
    return false;
}
*/
