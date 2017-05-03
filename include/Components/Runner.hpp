#ifndef RUNNER_HPP
#define RUNNER_HPP
#include <SFML/Graphics.hpp>
#include "Components/Warrior.hpp"
#include <iostream>

class Runner : public Warrior
{
    private:
        Animation m_animCloseAttack;
        //Animation m_animStrongAttack;
        
        // Close Attack
        float m_closeAttackStanima;
        float m_closeAttackDamageMul;
        //float m_strongAttackStanima;
        //float m_strongAttackDamageMul;

        // Dodge move
        bool m_isDodging;
        float m_dodgeStanima;
        float m_dodgeVelocity;
        // Total time of dodging
        float m_totalDodgeTime;
        // The time in seconds, while the current dodging running
        float m_curDodgeTime;
        // The direction of the dodging
        sf::Vector2f m_dodgeDir;

    public:
        Runner(RenderLayers layer, const int health, Textures textureId, 
                const ResourceHolder<sf::Texture, Textures> &textureHolder,
                const SpriteSheetMapHolder &spriteSheetMapHolder, 
                std::vector<Warrior*> &possibleTargetsInWord);

        virtual ~Runner();

        virtual void drawCurrent(sf::RenderTarget &target, 
                sf::RenderStates states) const;
    protected:
        virtual void weaponAdded();
    
    private:
        virtual void updateCurrent(float dt);
        virtual void updateAI(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);
        
        // Make the all sprites transparent
        void makeTransparent();
        // Make the all sprites intransparent
        void makeInTransparent();

        void startCloseAttack();
        void startDodging();
        void stopDodging();
};

#endif // RUNNER_HPP
