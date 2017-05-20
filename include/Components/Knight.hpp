#ifndef KNIGHT_HPP
#define KNIGHT_HPP
#include <SFML/Graphics.hpp>
#include "Components/Warrior.hpp"
#include <iostream>

class Item;

class Knight : public Warrior
{
    private:
        Animation m_animCloseAttack;
        //Animation m_animStrongAttack;
        
        sf::Vector2f m_shieldEquipPos;
        Item *m_shield;
        
        const float m_WeaponDamage;

        // Close Attack
        float m_closeAttackStanima;
        float m_closeAttackDamageMul;
    
        // Strong Attack
        bool m_isStrongAttackRunning;
        float m_strongAttackStanima;
        float m_strongAttackDamageMul;
        float m_strongAttackVelocity;
        // Total time of the strong attack
        float m_totalStrongAttackTime;
        // The time in seconds, while the current Storng attack is running
        float m_curStrongAttackTime;
        // The direction of the strong atack
        sf::Vector2f m_strongAttackDir;
             

    public:
        Knight(RenderLayers layer, const int health, const std::string &textureId, 
                const ResourceHolder<sf::Texture> &textureHolder,
                const SpriteSheetMapHolder &spriteSheetMapHolder, 
                std::vector<Warrior*> &possibleTargetsInWord);

        virtual ~Knight();
        
        Item *getShield() const;
        
        void startCloseAttack();
        void startStrongAttack();
        void stopStrongAttack();
        void startBlocking();
        void stopBlocking();
        
        virtual void handleDamage(Weapon *weapon);

        virtual void drawCurrent(sf::RenderTarget &target, 
                sf::RenderStates states) const;
    protected:

        virtual void weaponAdded();
    private:
        virtual void updateCurrent(float dt);
        virtual void updateAI(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);

};

#endif // KNIGHT_HPP
