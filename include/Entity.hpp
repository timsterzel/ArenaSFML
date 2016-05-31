#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"

enum class MoveDirections
{
    LEFT,
    RIGHT,
    UP,
    DOWN,
    NONE
};

class Entity : public SceneNode
{
    private:
        sf::Vector2f m_velocity;
        sf::Vector2f m_currentVelocity;
        MoveDirections m_moveDirection;

    public:
        Entity();

        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float velX, float velY);
        sf::Vector2f getVelocity() const;
        void setMoveDirection(MoveDirections moveDirection);
        MoveDirections getMoveDirection() const;

    private:
        virtual void updateCurrent(float dt);

};

#endif // ENTITY_HPP
