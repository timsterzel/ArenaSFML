#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include <SFML/Graphics.hpp>
#include "Collision/CollisionCircle.hpp"
#include "Components/Entity.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/ResourceHolder.hpp"

class Weapon;

class Warrior : public Entity
{
    protected:
        int m_maxHealth;
        int m_currentHealth;

    private:
        sf::Sprite m_sprite;
        Weapon *m_weapon;
        sf::Vector2f m_weaponPos;
        //CollisionCircle m_collisionCircle;

    public:
        Warrior(const int health, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder);

        int getCurrentHealth() const;
        void setCurrentHealth(const int health);

        void setWeapon(Weapon *weapon);
        Weapon* getWeapon() const;

        sf::Vector2f getWorldWeaponPos() const;

        bool isAlive() const;
        void damage(const int damage);
        void heal(const int health);

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        virtual void updateCurrent(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);
        void lookAt(sf::Vector2f pos);
};

#endif // WARRIOR_HPP
