#ifndef WEAPON_HPP
#define WEAPON_HPP
#include <SFML/Graphics.hpp>
#include "Components/Item.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/ResourceHolder.hpp"
#include "set"

class Weapon : public Item
{
    protected:
        float m_damage;
        // The damage multiplicator is multiplied with the standart damage to get 
        // the final damage
        float m_damageMultiplicator;

        // A Id which should be added by every attack the weapon does, 
        // so the attack is clearly identifiable
        std::string m_ID;
        // Store the ids of the warriors which was attacked from the actual attacked
        // (That make it possible that only the first hit of a attack counts)
        std::set<std::string> m_hitIDs;

    public:
        Weapon(RenderLayers layer, const float damage, Textures textureId, 
                const ResourceHolder<sf::Texture, Textures> &textureHolder);
        Weapon(RenderLayers layer, const float damage, const sf::Texture &texture, 
                const sf::IntRect &rect);
        Weapon(RenderLayers layer, const float damage, const sf::Texture &texture, 
                const std::vector<sf::IntRect> frameRects, bool centerOrigin, 
                float totalTime, bool repeat = true);
        virtual ~Weapon();
        
        float getTotalDamage() const;
        void setStandartDamage(const float damage);
        void setDamageMultiplicator(float multiplicator);
        
        const std::string& getAttackID() const;
        void addHitID(const std::string& id);
        // Return if the given id was already hittet by the acutal attack
        bool wasIDAlreadyAttacked(const std::string& id);
        

        // Creates a new attackID
        void startNewAttack();
};

#endif // WEAPON_HPP
