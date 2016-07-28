#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>
#include "Components/SceneNode.hpp"

class Entity : public SceneNode
{
    protected:
        sf::Vector2f m_velocity;
        sf::Vector2f m_currentVelocity;
        float m_width;
        float m_height;
    private:

    public:
        Entity();

        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float velX, float velY);
        sf::Vector2f getVelocity() const;
        sf::Vector2f getCurrentVelocity() const;
        float getWidth() const;
        void setWidth(float width);
        float getHeight() const;
        void setHeight(float height);
        // Move the actual object the given length by the acutal direction (velocity)
        void moveInActualDirection(const float length);
        void moveInDirection(const sf::Vector2f direction, const float length);

        // Override transformables setRotation() method with virtual so we can modify it in classes
        virtual void setRotation(float angle);
        // Override transformables rotate() method with virtual so we can modify it in classes
        virtual void rotate(float angle);
        // We have to override this method, because the entity can have a width an height
        //virtual sf::Vector2f getWorldCenterPosition() const;

    private:
        virtual void updateCurrent(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);

};

#endif // ENTITY_HPP
