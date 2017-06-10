#include "Components/Wizard.hpp"
#include "Components/Weapon.hpp"
#include "Components/Item.hpp"
#include "Collision/CollisionRect.hpp"
#include "Collision/CollisionHandler.hpp"
#include "Calc.hpp"
#include "Helpers.hpp"
#include "DebugHelpers.hpp"
#include <iostream>

Wizard::Wizard(RenderLayers layer, const int health, const std::string &textureId, 
        const ResourceHolder<sf::Texture> &textureHolder,
        const SpriteSheetMapHolder &spriteSheetMapHolder, 
        std::vector<Warrior*> &possibleTargetsInWord)
: Warrior(layer, health, textureId, textureHolder, spriteSheetMapHolder, 
        possibleTargetsInWord)

, m_animFireballAttack( nullptr, false )
//, m_animStrongAttack( nullptr, false )
// Close Attack
, m_fireballAttackStanima{ 10.f }
, m_fireballDamage{ 15.f }
, m_isHealing{ false }
, m_healRestoreRate{ 10.f }
, m_healStanimaRate{ 40.f }
, m_currentHealColorStep{ 0 }
, m_totalHealColorStepTime{ 0.3f }
, m_currentHealColorStepTime{ 0.f }
{
    addType(WorldObjectTypes::WIZARD);
    setVelocity(70.f);
    // Animation
    std::vector<AnimationStepMovement>  stickMovementStepsFireball;
    stickMovementStepsFireball.push_back({ -2.f, { 0, 1 },  0.1f });
    stickMovementStepsFireball.push_back({ 2.f, { 0, 1 },  0.1f });
    m_animFireballAttack.setMovementSteps(stickMovementStepsFireball);
    /*
    std::vector<AnimationStepRotation>  swordRoationStepsCloseAtt;
    swordRoationStepsCloseAtt.push_back({ 0.f, -60.f,  0.3f });
    m_animFireballAttack.setRotationSteps(swordRoationStepsCloseAtt);
    */
    std::unique_ptr<Weapon> stick(new Weapon(RenderLayers::WEAPON, 10.f, 
                textureHolder.get(textureId), 
                spriteSheetMapHolder.getRectData(textureId, "stick")));
    stick->setPosition(0.f, 0.f);
    stick->setOrigin(0.f, -10.f);
    std::unique_ptr<CollisionShape> collisionShapeSword(new CollisionRect(
                { stick->getSpriteWidth(), stick->getSpriteHeight() }));
    stick->setCollisionShape(std::move(collisionShapeSword));
    setWeapon(stick.get());
    attachChild(std::move(stick));

    std::unique_ptr<CollisionShape> closeCombatArea(new CollisionCircle(9.f));
    m_closeCombatArea = std::move(closeCombatArea);
    m_closeCombatArea->setParent(this);
    m_closeCombatArea->setPosition(9.f, 0.f);
    // Load frame rects of fireball
    m_fireballFrameRects.push_back(
        m_spriteSheetMapHolder.getRectData("fireball", "fireball_1"));
    m_fireballFrameRects.push_back(
        m_spriteSheetMapHolder.getRectData("fireball", "fireball_2"));
    m_fireballFrameRects.push_back(
        m_spriteSheetMapHolder.getRectData("fireball", "fireball_3"));
    m_fireballFrameRects.push_back(
        m_spriteSheetMapHolder.getRectData("fireball", "fireball_4"));
    m_fireballFrameRects.push_back(
        m_spriteSheetMapHolder.getRectData("fireball", "fireball_5"));
    m_fireballFrameRects.push_back(
        m_spriteSheetMapHolder.getRectData("fireball", "fireball_6"));
    // Collision shape
    std::unique_ptr<CollisionShape> collisionShape{ 
        std::make_unique<CollisionCircle>(10.f) };
    setCollisionShape(std::move(collisionShape));
}

Wizard::~Wizard()
{

}

void Wizard::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    Warrior::drawCurrent(target, states);
}

void Wizard::updateCurrent(float dt)
{
    Warrior::updateCurrent(dt);
    if (m_animFireballAttack.isRunning())
    {
        m_animFireballAttack.update(dt);
    }
    if (m_isHealing)
    {
        float healVal{ m_healRestoreRate * dt };
        float removeStanimaVal{ m_healStanimaRate * dt };
        float currentStanima{ getCurrentStanima() };
        float newStanima{ currentStanima - removeStanimaVal };
        // If warrior has not enough stanima, only restore as much health as 
        // stanima is there
        if (newStanima < 0.f)
        {
            healVal = currentStanima / m_healRestoreRate;
            removeStanimaVal = currentStanima;
        }        
        removeStanima(removeStanimaVal);
        heal(healVal);
        updateHealColor(dt);
        if (getCurrentStanima() <= 0.f)
        {
            stopHealing();
        }
    }
}

void Wizard::updateHealColor(float dt)
{
    m_currentHealColorStepTime += dt;
	float colPos{ m_currentHealColorStepTime / m_totalHealColorStepTime  };
    if (m_currentHealColorStepTime > m_totalHealColorStepTime)
    {
        m_currentHealColorStepTime = 0.f;
        m_currentHealColorStep++;
        colPos = 0.f;
		if (m_currentHealColorStep > 1)
		{
			m_currentHealColorStep = 0;
		}
    }
    sf::Color curCol;
    if (m_currentHealColorStep == 0)
    {
	    curCol = Helpers::lerbRGBColor(
            sf::Color::White, sf::Color::Red, colPos);
    }
    else
    {
	    curCol = Helpers::lerbRGBColor(
            sf::Color::Red, sf::Color::White, colPos);
    }
    applyColor(curCol);
}

void Wizard::onCommandCurrent(const Command &command, float dt)
{
    // Do command handling of parent class
    //Entity::onCommand(command, dt);
    Warrior::onCommandCurrent(command, dt);
    if (command.getWorldObjectType() & m_type)
    {
        m_currentVelocity = 0.f;
        m_currentDirection.x = 0.f;
        m_currentDirection.y = 0.f;
        switch (command.getCommandType())
        {
            case CommandTypes::ACTION_1:
                startFireballAttack();
                break;
            case CommandTypes::ACTION_2:
                //startRoundAttack();
                break;
            case CommandTypes::SPECIAL_ACTION:
                break;
            // Not really blocking, but the same key
            case CommandTypes::ACTION_START:
                startHealing();
                break;
            case CommandTypes::ACTION_STOP:
                stopHealing();
                break;
            /*
            case CommandTypes::START_BLOCKING:
                startBlocking();
                break;
            case CommandTypes::STOP_BLOCKING:
                stopBlocking();
                break;
            */
            default:
                break;

        }
        moveInActualDirection(m_currentVelocity * dt);
    }
}

void Wizard::updateAI(float dt)
{
    /*
    m_isMoving = false;
    Warrior::updateAI(dt);
    if (!m_actualTarget)
    {
        return;
    }

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
    */
}

void Wizard::startFireballAttack()
{
    if (m_weapon && !m_animFireballAttack.isRunning() &&  
            m_currentStamina >= m_fireballAttackStanima && !m_isHealing)
    {
        m_animFireballAttack.start();
        SceneNode* rootNode{ getRootSceneNode() };

        std::unique_ptr<Weapon> fireball{ 
            std::make_unique<Weapon>(RenderLayers::WEAPON,
                    m_fireballDamage,
                    m_textureHolder.get("fireball"), 
                    m_fireballFrameRects, 
                    true,
                    0.5f) };
        
        // Add id of wizard to "HitID", so the weapon asume that the wizard was
        // already attacked, so the wizard is not damaged by colliding with fireball
        fireball->addHitID(getID());
        fireball->setDebugName("Fireball");
        fireball->setVelocity(200.f);
        // We have to add a distance to the fireball in the direction the wizards
        // look, because the fireball is higher then the wizard and the fireball
        // should not stick out behind the warrior
        sf::Vector2f lookDir{ 
            Calc::degAngleToDirectionVector(getRotation() + 90.f) };
        sf::Vector2f spawnDist{ lookDir.x * 10.f, lookDir.y * 10.f };
        sf::Vector2f pos{ getWorldPosition() + spawnDist };
        fireball->setPosition(pos);
        
        fireball->setRotationDefault(getRotation());
        fireball->setCurrentDirection(
                Calc::degAngleToDirectionVector(fireball->getRotation() + 90.f));
        fireball->addType(WorldObjectTypes::PROJECTILE);
        std::unique_ptr<CollisionShape> collisionShape{
            std::make_unique<CollisionRect>(
                    sf::Vector2f(fireball->getWidth(), fireball->getHeight()))};
        fireball->setCollisionShape(std::move(collisionShape));
        fireball->setIsCollisionCheckOn(true);
        rootNode->attachChild(std::move(fireball));
        removeStanima(m_fireballAttackStanima);
    }
}

void Wizard::startHealing()
{
    m_isHealing = true;
    m_currentHealColorStepTime = 0.f;
    m_currentHealColorStep = 0;
}

void Wizard::stopHealing()
{
    m_isHealing = false;
    removeColorEffects();
}

void Wizard::applyColor(sf::Color color)
{
    m_leftShoe->getSprite().setColor(color);
    m_rightShoe->getSprite().setColor(color);
    m_upperBody->getSprite().setColor(color);
    if (m_weapon)
    {
        m_weapon->getSprite().setColor(color);
    }
}
        
void Wizard::removeColorEffects()
{
    m_leftShoe->getSprite().setColor(sf::Color::White);
    m_rightShoe->getSprite().setColor(sf::Color::White);
    m_upperBody->getSprite().setColor(sf::Color::White);
    if (m_weapon)
    {
        m_weapon->getSprite().setColor(sf::Color::White);
    }
}

void Wizard::weaponAdded()
{
    m_animFireballAttack.setParent(m_weapon);
}
