#include "Components/Knight.hpp"
#include <Components/Weapon.hpp>
#include <Collision/CollisionRect.hpp>
#include <iostream>

Knight::Knight(RenderLayers layer, const int health, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder, const SpriteSheetMapHolder &spriteSheetMapHolder)
: Warrior(layer, health, textureId, textureHolder, spriteSheetMapHolder)
{
    std::vector<AnimationStepRotation>  swordRoationSteps;
    swordRoationSteps.push_back({ 0.f, -60.f,  0.5f });
    m_animationWeapon.setRotationSteps(swordRoationSteps);

    std::unique_ptr<Weapon> sword(new Weapon(RenderLayers::WEAPON, 60, Textures::SWORD, textureHolder));
    sword->setType(WorldObjectTypes::WEAPON);
    sword->setPosition(0.f, 0.f);
    //swordPlayer->setRotationPoint(0.f, swordPlayer->getSpriteHeight() / 2.f);
    sword->setEquipPoint(-10.f, 0.f);
    std::unique_ptr<CollisionShape> collisionShapeSword(new CollisionRect({ sword->getSpriteWidth(), sword->getSpriteHeight() }));
    sword->setCollisionShape(std::move(collisionShapeSword));
    setWeapon(sword.get());
    attachChild(std::move(sword));
    std::cout << "After sowrd Init" << std::endl;

    /*
    std::vector<AnimationStepMovement>  swordMovementSteps;
    swordMovementSteps.push_back({ sf::Vector2f(0.f, 0.f), 100.f, sf::Vector2f(10.f, 0.f) , 1.5f });
    m_animationSword.setMovementSteps(swordMovementSteps);
    */
}

void Knight::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    Warrior::drawCurrent(target, states);
}

void Knight::updateCurrent(float dt)
{
    Warrior::updateCurrent(dt);
}

void Knight::onCommandCurrent(const Command &command, float dt)
{
    // Do command handling of parent class
    //Entity::onCommand(command, dt);
    Warrior::onCommandCurrent(command, dt);
    if (command.getWorldObjectType() == m_type)
    {
        m_currentVelocity.x = 0.f;
        m_currentVelocity.y = 0.f;
        switch (command.getCommandType())
        {
            case CommandTypes::ATTACK:
                if (!m_animationWeapon.isRunning())
                {
                    m_animationWeapon.start();
                    m_weapon->setIsCollisionCheckOn(true);
                }
                break;
        }
        // Move is the same as setPosition(getPosition() + offset) of the sf::Transformable class
        move(m_currentVelocity * dt);
    }
}



