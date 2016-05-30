#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"

class Entity : public SceneNode
{
    protected:


    private:
        sf::Vector2f m_velocity;


    public:
        Entity();

        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float velX, float velY);
        sf::Vector2f getVelocity();

    private:
        virtual void updateCurrent(float dt);

};

#endif // ENTITY_HPP
