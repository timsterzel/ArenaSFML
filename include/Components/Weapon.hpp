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
        // The point of which it should be rotated
        sf::Vector2f m_rotationPoint;

        // The point on the weapon on which the weapon is connected to the parent, relative to the origin
        sf::Vector2f m_relEquipPoint;

    public:
        Weapon(const int damage, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder);

        virtual ~Weapon();

        int getDamage() const;
        void setDamage(const int damage);

        int getSpriteWidth() const;
        int getSpriteHeight() const;

        bool isAttacking() const;

        void setRotationPoint(sf::Vector2f point);
        void setRotationPoint(float x, float y);
        sf::Vector2f getRotationPoint() const;

        virtual void setRotation(float angle);
        //void rotateAround(sf::Vector2f pos, float degrees);
        void rotate(float angle);

        void setEquipPoint(float x, float y);
        void equip(sf::Vector2f parentEqiupPos);

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        virtual void updateCurrent(float dt);
};

#endif // WEAPON_HPP
