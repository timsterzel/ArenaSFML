#include "Collision/CollisionInfo.hpp"
#include "Components/SceneNode.hpp"

CollisionInfo::CollisionInfo(const bool isCollision)
: m_isCollision{ isCollision }
, m_length{ 0.f }
, m_resolveDirFirst{ 0.f, 0.f }
, m_resolveDirSecond{ 0.f, 0.f }
, m_collidedFirst{ nullptr }
, m_collidedSecond { nullptr }
{

}

CollisionInfo::CollisionInfo(const bool isCollision, const float length, const sf::Vector2f resolveDirFirst,
                            const sf::Vector2f resolveDirSecond, SceneNode *const collidedFirst,
                            SceneNode *const collidedSecond)
: m_isCollision{ isCollision }
, m_length{ length }
, m_resolveDirFirst{ resolveDirFirst }
, m_resolveDirSecond{ resolveDirSecond }
, m_collidedFirst{ collidedFirst }
, m_collidedSecond{ collidedSecond }
{

}

bool CollisionInfo::isCollision() const
{
    return m_isCollision;
}

float CollisionInfo::getLength() const
{
    return m_length;
}

sf::Vector2f CollisionInfo::getResolveDirOfFirst() const
{
    return m_resolveDirFirst;
}

sf::Vector2f CollisionInfo::getResolveDirOfSecond() const
{
    return m_resolveDirSecond;
}

SceneNode* CollisionInfo::getCollidedFirst() const
{
    return m_collidedFirst;
}

SceneNode* CollisionInfo::getCollidedSecond() const
{
    return m_collidedSecond;
}
