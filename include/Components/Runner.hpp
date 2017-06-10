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
        
        // Round attack
        bool m_isRoundAttacking;
        float m_roundAttackStanima;
        float m_roundAttackDamageMul;
        // The current rotation in degrees
        float m_roundAttackCurRot;
        // The total rotation in degrees
        float m_roundAttackTotalRot;
        // The angle in degrees per second
        float m_roundAttackAngleVel;
        // The Runners rotation by starting attack
        float m_startRotationRoundAttack;
        
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
        Runner(RenderLayers layer, const int health, const std::string &textureId,
                const ResourceHolder<sf::Texture> &textureHolder,
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
        void stopCloseAttack();
        void startRoundAttack();
        void stopRoundAttack();
        void startDodging();
        void stopDodging();
};

#endif // RUNNER_HPP
