#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <SFML/Graphics.hpp>
#include "Components/Item.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/ResourceHolder.hpp"

class Weapon : public Item
{
    protected:
        float m_damage;
        // The damage multiplicator is multiplied with the standart damage to get 
        // the final damage
        float m_damageMultiplicator;

        // A Id which should be added by every attack the weapon does, 
        // so the attack is clearly identifiable
        std::string m_attackID;
    public:
        Weapon(RenderLayers layer, const float damage, Textures textureId, 
                const ResourceHolder<sf::Texture, Textures> &textureHolder);
        Weapon(RenderLayers layer, const float damage, const sf::Texture &texture, 
                const sf::IntRect &rect);
        virtual ~Weapon();
        
        float getTotalDamage() const;
        void setStandartDamage(const float damage);
        void setDamageMultiplicator(float multiplicator);
        
        const std::string& getAttackID() const;
        
        // Creates a new attackID
        void startNewAttack();
};

#endif // WEAPON_HPP
