#include "Collision/CollisionCircle.hpp"
#include "Collision/CollisionHandler.hpp"

CollisionCircle::CollisionCircle(float radius)
: m_circleShape{ radius }
{
    m_circleShape.setFillColor(sf::Color(255, 0, 0, 160));
    //m_circleShape.setFillColor(sf::Color::Red);
    m_circleShape.setOrigin(radius, radius);
}

void CollisionCircle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_circleShape, states);
}

bool CollisionCircle::isColliding(const CollisionShape &collider) const
{
    return collider.isColliding(*this);
}

bool CollisionCircle::isColliding(const CollisionCircle &collider) const
{
    return CollisionHandler::isColliding(*this, collider);
}

bool CollisionCircle::isColliding(const CollisionRect &collider) const
{
    return CollisionHandler::isColliding(*this, collider);
}
