#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <SFML/Graphics.hpp>
#include "Components/Entity.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/ResourceHolder.hpp"

class Weapon : public Entity
{
    protected:
        int m_damage;

    private:
        sf::Sprite m_sprite;
        bool m_isAttacking;
        // The point on the weapon on which the weapon is connected to the parent, relative to the origin
        //sf::Vector2f m_relEquipPoint;
        //sf::Vector2f m_absEquipPoint;


    public:
        Weapon(const int damage, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder);

        virtual ~Weapon();

        int getDamage() const;
        void setDamage(const int damage);

        int getSpriteWidth() const;
        int getSpriteHeight() const;

        bool isAttacking() const;

        //void setEquipPoint(float x, float y);

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        virtual void updateCurrent(float dt);
};

#endif // WEAPON_HPP
