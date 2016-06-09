#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include <SFML/Graphics.hpp>
#include "Collision/CollisionCircle.hpp"
#include "Components/Entity.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/ResourceHolder.hpp"

class Warrior : public Entity
{
    protected:
        int m_maxHealth;
        int m_currentHealth;

    private:
        sf::Sprite m_sprite;
        //CollisionCircle m_collisionCircle;

    public:
        Warrior(const int health, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder);

        int getCurrentHealth() const;
        void setCurrentHealth(const int health);

        bool isAlive() const;
        void damage(const int damage);
        void heal(const int health);

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        virtual void onCommandCurrent(const Command &command, float dt);
        void lookAt(sf::Vector2f pos);
};

#endif // WARRIOR_HPP
