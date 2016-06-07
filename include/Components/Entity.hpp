#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <SFML/Graphics.hpp>
#include "Components/SceneNode.hpp"



class Entity : public SceneNode
{
    protected:
        sf::Vector2f m_velocity;
        sf::Vector2f m_currentVelocity;

    private:

    public:
        Entity();

        void setVelocity(sf::Vector2f velocity);
        void setVelocity(float velX, float velY);
        sf::Vector2f getVelocity() const;

    private:
        virtual void updateCurrent(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);

};

#endif // ENTITY_HPP
