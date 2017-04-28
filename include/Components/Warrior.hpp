#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include <SFML/Graphics.hpp>
#include "Animation/Animation.hpp"
#include "Collision/CollisionCircle.hpp"
#include "Components/Entity.hpp"
#include "Components/SpriteNode.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/ResourceHolder.hpp"
#include "Resources/SpriteSheetMapHolder.hpp"

class Weapon;

class Warrior : public Entity
{

    protected:
        // A random generated id (should be unique)
        std::string m_ID;

        float m_maxHealth;
        float m_currentHealth;

        float m_maxStamina;
        float m_currentStamina;
        // The rate whith the stanima automatic fill up
        float m_stanimaRefreshRate;
        // Used to check if movement animation shout get updated
        bool m_isMoving;
        bool m_isBlocking;
        // The id of the attack which was blocked (Attacks with this id has no effect)
        std::string m_blockedAttackID;
        // Delete m_sprite later
        sf::Sprite m_sprite;
        SpriteNode *m_leftShoe;
        SpriteNode *m_rightShoe;
        Weapon *m_weapon;
        SpriteNode *m_upperBody;
        sf::Vector2f m_weaponPos;

        Animation m_animationLeftShoe;
        Animation m_animationRightShoe;
        //CollisionCircle m_collisionCircle;
        /*
        float m_attack1Stanima;
        // The multiplicator of of the attack for damage calculation
        float m_attack1DamageMul;
        float m_attack2Stanima;
        // The multiplicator of of the attack for damage calculation
        float m_attack2DamageMul;
        */
        std::unique_ptr<CollisionShape> m_closeCombatArea;

        // Used for AI
        bool m_isAiActive;
        std::vector<Warrior*> &m_possibleTargetsInWord;
        Warrior *m_actualTarget;


    public:
        Warrior(RenderLayers layer, const float health, Textures textureId, 
                const ResourceHolder<sf::Texture, Textures> &textureHolder,
                const SpriteSheetMapHolder &spriteSheetMapHolder, 
                std::vector<Warrior*> &possibleTargetsInWord);
        virtual ~Warrior();
        
        const std::string& getID();

        float getCurrentHealth() const;
        void setCurrentHealth(const float health);
        
        float getMaxHealth() const;

        float getCurrentStanima() const;
        void setCurrentStanima(const float stanima);

        bool isBlocking() const;
        const std::string& getBlockedAttackID() const;
        void setBlockedAttackID(const std::string id);

        void setWeapon(Weapon *weapon);
        Weapon* getWeapon() const;

        sf::Vector2f getWorldWeaponPos() const;

        void setIsAiActive(bool isAiActive);
        void setActualTarget(Warrior *target);
        //int getDamage() const;

        bool isAlive() const;
        void damage(const float damage);
        void heal(const float health);
        void removeStanima(float stanima);
        void addStanima(float stanima);

        virtual void drawCurrent(sf::RenderTarget &target, 
                sf::RenderStates states) const;


    protected:
        void setBodyParts(SpriteNode *leftShoe, SpriteNode *rightShoe, 
                SpriteNode *upperBody);

        virtual void updateCurrent(float dt);
        virtual Warrior* determineActualTarget() const;
        virtual void updateAI(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);
        void lookAt(sf::Vector2f pos);
        virtual void weaponAdded();
        // The command which are for every Warrior equal
        //void onCommandCurrentWarrior(const Command &command, float dt);
};

#endif // WARRIOR_HPP
