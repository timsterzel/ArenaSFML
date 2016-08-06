#ifndef WARRIOR_HPP
#define WARRIOR_HPP
#include <SFML/Graphics.hpp>
#include "Animation/Animation.hpp"
#include "Collision/CollisionCircle.hpp"
#include "Components/Entity.hpp"
#include "Components/SpriteNode.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/ResourceHolder.hpp"

class Weapon;

class Warrior : public Entity
{
    protected:
        int m_maxHealth;
        int m_currentHealth;

        // Delete m_sprite later
        sf::Sprite m_sprite;
        SpriteNode *m_leftShoe;
        SpriteNode *m_rightShoe;
        Weapon *m_weapon;
        SpriteNode *m_upperBody;
        sf::Vector2f m_weaponPos;

        Animation m_animationWeapon;
        Animation m_animationLeftShoe;
        Animation m_animationRightShoe;
        //CollisionCircle m_collisionCircle;

    public:
        Warrior(const int health, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder);

        int getCurrentHealth() const;
        void setCurrentHealth(const int health);

        void setBodyParts(SpriteNode *leftShoe, SpriteNode *rightShoe, SpriteNode *upperBody);
        void setWeapon(Weapon *weapon);
        Weapon* getWeapon() const;

        sf::Vector2f getWorldWeaponPos() const;

        bool isAlive() const;
        void damage(const int damage);
        void heal(const int health);

        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;


    protected:
        virtual void updateCurrent(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);
        void lookAt(sf::Vector2f pos);
        // The command which are for every Warrior equal
        //void onCommandCurrentWarrior(const Command &command, float dt);
};

#endif // WARRIOR_HPP
