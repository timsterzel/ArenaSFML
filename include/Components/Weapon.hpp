#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <SFML/Graphics.hpp>
#include "Components/Entity.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/ResourceHolder.hpp"

class Weapon : public Entity
{
    protected:
        float m_damage;
        // The damage multiplicator is multiplied with the standart damage to get the final damage
        float m_damageMultiplicator;

    private:
        sf::Sprite m_sprite;
        //bool m_isAttacking;
        // The point of which it should be rotated
        sf::Vector2f m_rotationPoint;

        // The point on the weapon on which the weapon is connected to the parent, relative to the origin
        sf::Vector2f m_relEquipPoint;


    public:
        Weapon(RenderLayers layer, const float damage, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder);
        Weapon(RenderLayers layer, const float damage, const sf::Texture &texture, const sf::IntRect &rect);
        virtual ~Weapon();

        float getTotalDamage() const;
        void setStandartDamage(const float damage);
        void setDamageMultiplicator(float multiplicator);

        float getSpriteWidth() const;
        float getSpriteHeight() const;

        void setRotationPoint(sf::Vector2f point);
        void setRotationPoint(float x, float y);
        sf::Vector2f getRotationPoint() const;

        virtual void setRotation(float angle);
        //void rotateAround(sf::Vector2f pos, float degrees);
        void rotate(float angle);
        
        // The point on the item where it is added to the parent
        // E.g. the equipPoint of a sword is its handle
        void setEquipPoint(float x, float y);
        // The point relative to the parent where the item is added on the parent
        // E.g. when you want to equip a sword to a character, the parentEquip pos is
        // its hand
        void equip(sf::Vector2f parentEqiupPos);

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;

    private:
        virtual void updateCurrent(float dt);
};

#endif // WEAPON_HPP
