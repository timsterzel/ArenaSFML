#include "Collision/CollisionRect.hpp"
#include "Collision/CollisionHandler.hpp"

CollisionRect::CollisionRect(sf::Vector2f rectSize)
: m_rectShape{ rectSize }
{
    m_rectShape.setFillColor(sf::Color(255, 0, 0, 160));
    //m_circleShape.setFillColor(sf::Color::Red);
    m_rectShape.setOrigin(rectSize.x / 2.f, rectSize.y / 2.f);
}

void CollisionRect::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_rectShape, states);
}

bool CollisionRect::isColliding(const Collision &collider) const
{
    return collider.isColliding(*this);
}

bool CollisionRect::isColliding(const CollisionCircle &collider) const
{
    return CollisionHandler::isColliding(*this, collider);
}

bool CollisionRect::isColliding(const CollisionRect &collider) const
{
    return CollisionHandler::isColliding(*this, collider);
}
