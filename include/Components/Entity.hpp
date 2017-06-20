#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>
#include "Components/SceneNode.hpp"

class Entity : public SceneNode
{
    protected:
        // The velocity with which the entity can move
        float m_velocity;
        // The current velocity of the entity
        float m_currentVelocity;
        // The current direction of the entity
        // The mass of the entity
        float m_mass;
        sf::Vector2f m_currentDirection;
        float m_width;
        float m_height;
    
    public:
        explicit Entity(RenderLayers layer);
        virtual ~Entity();

        void setVelocity(float velocity);
        float getVelocity() const;
        void setCurrentVelocity(float currentVelocity);
        float getCurrentVelocity() const;
        float getMass() const;
        void setMass(float mass);
        void setCurrentDirection(sf::Vector2f currentDirection);
        sf::Vector2f getCurrentDirection() const;

        float getWidth() const;
        void setWidth(float width);
        float getHeight() const;
        void setHeight(float height);
        // Move the actual object the given length by the acutal direction (velocity)
        void moveInActualDirection(const float length);
        void moveInDirection(const sf::Vector2f direction, const float length);
   protected:
        virtual void updateCurrent(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);
};

#endif // ENTITY_HPP
