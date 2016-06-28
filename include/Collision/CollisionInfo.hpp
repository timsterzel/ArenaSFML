#ifndef COLLISIONINFO_HPP
#define COLLISIONINFO_HPP
#include <SFML/Graphics.hpp>

class SceneNode;

class CollisionInfo
{
    private:
        bool m_isCollision;
        float m_length;
        // The direction which is used to resolve the collision
        sf::Vector2f m_resolveDirFirst;
        sf::Vector2f m_resolveDirSecond;
        SceneNode *const m_collidedFirst;
        SceneNode *const m_collidedSecond;

    public:
        explicit CollisionInfo(const bool isCollision);
        CollisionInfo(const bool isCollision, const float length, const sf::Vector2f resolveDirFirst,
        const sf::Vector2f resolveDirSecond, SceneNode *const collidedFirst, SceneNode *const collidedSecond);

        bool isCollision() const;
        float getLength() const;
        sf::Vector2f getResolveDirOfFirst() const;
        sf::Vector2f getResolveDirOfSecond() const;
        SceneNode* getCollidedFirst() const;
        SceneNode* getCollidedSecond() const;
};

#endif // COLLISIONINFO_HPP
