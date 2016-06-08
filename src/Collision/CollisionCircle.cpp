#include "Collision/CollisionCircle.hpp"

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

bool CollisionCircle::isColliding(const Collision &collider) const
{

}

bool CollisionCircle::isColliding(const CollisionCircle &collider) const
{

}
