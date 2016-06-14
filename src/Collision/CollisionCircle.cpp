#include "Collision/CollisionCircle.hpp"
#include "Collision/CollisionHandler.hpp"

CollisionCircle::CollisionCircle(float radius)
: m_radius{ radius }
{

}

float CollisionCircle::getRadius() const
{
    return m_radius;
}

void CollisionCircle::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    sf::CircleShape circleShape{ m_radius };
    circleShape.setFillColor(sf::Color(255, 0, 0, 160));
    circleShape.setOrigin(m_radius, m_radius);
    target.draw(circleShape, states);
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
