#include "Components/Knight.hpp"
#include <Components/Weapon.hpp>
#include <Collision/CollisionRect.hpp>
#include <Collision/CollisionHandler.hpp>
#include <iostream>

Knight::Knight(RenderLayers layer, const int health, Textures textureId, const ResourceHolder<sf::Texture, Textures> &textureHolder, const SpriteSheetMapHolder &spriteSheetMapHolder)
: Warrior(layer, health, textureId, textureHolder, spriteSheetMapHolder)
, m_isBlocking{ false }
{
    std::vector<AnimationStepRotation>  swordRoationSteps;
    swordRoationSteps.push_back({ 0.f, -60.f,  0.3f });
    m_animationWeapon.setRotationSteps(swordRoationSteps);

    //std::unique_ptr<Weapon> sword(new Weapon(RenderLayers::WEAPON, 60, Textures::SWORD, textureHolder));
    std::unique_ptr<Weapon> sword(new Weapon(RenderLayers::WEAPON, 60, textureHolder.get(textureId), spriteSheetMapHolder.getRectData(textureId, "sword")));
    sword->setType(WorldObjectTypes::WEAPON);
    sword->setPosition(0.f, 0.f);
    //swordPlayer->setRotationPoint(0.f, swordPlayer->getSpriteHeight() / 2.f);
    sword->setEquipPoint(-10.f, 0.f);
    std::unique_ptr<CollisionShape> collisionShapeSword(new CollisionRect({ sword->getSpriteWidth(), sword->getSpriteHeight() }));
    sword->setCollisionShape(std::move(collisionShapeSword));
    setWeapon(sword.get());
    attachChild(std::move(sword));
    std::cout << "After sowrd Init" << std::endl;

    std::unique_ptr<CollisionShape> closeCombatArea(new CollisionCircle(9.f));
    m_closeCombatArea = std::move(closeCombatArea);
    m_closeCombatArea->setParent(this);
    m_closeCombatArea->setPosition(9.f, 0.f);
    m_closeCombatArea->setDraw(true);
    /*
    std::vector<AnimationStepMovement>  swordMovementSteps;
    swordMovementSteps.push_back({ sf::Vector2f(0.f, 0.f), 100.f, sf::Vector2f(10.f, 0.f) , 1.5f });
    m_animationSword.setMovementSteps(swordMovementSteps);
    */
}

Knight::~Knight()
{
    std::cout << "Destructor Knight" << std::endl;
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
        m_currentVelocity = 0.f;
        m_currentDirection.x = 0.f;
        m_currentDirection.y = 0.f;
        switch (command.getCommandType())
        {
            case CommandTypes::ATTACK:
                startCloseAttack();
                break;
            case CommandTypes::START_BLOCKING:
                startBlocking();
                break;
            case CommandTypes::STOP_BLOCKING:
                stopBlocking();
                break;
            default:
                break;

        }

        // Move is the same as setPosition(getPosition() + offset) of the sf::Transformable class
        //move(m_currentVelocity * dt);
        //moveInDirection(m_currentDirection, m_currentVelocity * dt);
        moveInActualDirection(m_currentVelocity * dt);
    }
}

void Knight::updateAI(float dt)
{
    m_isMoving = false;
    Warrior::updateAI(dt);
    lookAt(m_actualTarget->getPosition());
    CollisionInfo collisionInfo = m_closeCombatArea->isColliding(*m_actualTarget->getCollisionShape());
    if (collisionInfo.isCollision())
    {
        startCloseAttack();
    }
    else
    {
        // Follow target
        m_currentVelocity = m_velocity;
        m_currentDirection = m_actualTarget->getWorldPosition() - getWorldPosition();
        m_isMoving = true;
        moveInActualDirection(m_currentVelocity * dt);
    }
}

void Knight::startCloseAttack()
{
    if (m_weapon && !m_animationWeapon.isRunning())
    {
        m_animationWeapon.start();
        m_weapon->setIsCollisionCheckOn(true);
    }
}

void Knight::startBlocking()
{
    m_animationWeapon.stop();
    std::cout << "startBlocking" << std::endl;
    // Knight can only block with a weapon
    if (m_weapon)
    {
        m_isBlocking = true;
        m_weapon->setRotation(-30.f);
    }
}

void Knight::stopBlocking()
{
    std::cout << "stopBlocking" << std::endl;
    m_isBlocking = false;
    if (m_weapon)
    {
        m_weapon->setRotation(0.f);
    }
}


