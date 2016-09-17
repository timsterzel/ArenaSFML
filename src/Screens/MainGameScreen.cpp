#include "Screens/MainGameScreen.hpp"
#include "Collision/CollisionShape.hpp"
#include "Collision/CollisionCircle.hpp"
#include "Collision/CollisionRect.hpp"
#include "Components/SpriteNode.hpp"
#include "Components/Warrior.hpp"
#include "Components/Weapon.hpp"
#include "Components/Knight.hpp"
#include "Calc.hpp"
#include <memory>
#include "Game.hpp"

MainGameScreen::MainGameScreen(ScreenStack *screenStack, Context context)
: Screen(screenStack, context)
, m_isGamePaused{ false }
, m_showCollisionInfo{ false }
, m_worldBounds{ 0.f, 0.f, 6000.f, 6000.f }
, m_playerWarrior{ nullptr }
{
    buildScene();
}

MainGameScreen::~MainGameScreen()
{

}

void MainGameScreen::buildScene()
{
    std::cout << "MainGameScreen::buildScene" << std::endl;
    // Play music
    m_context.music->play(Musics::GAMETHEME01);

    /*
    for (std::size_t i = { 0 }; i < Layers::COUNT; i++)
    {
        // Use std::unique_ptr<SceneNode>
        SceneNode::Ptr layer(new SceneNode());
        m_sceneLayers[i] = layer.get();
        m_sceneGraph.attachChild(std::move(layer));
    }
    */

    sf::Texture &texture = m_context.textureHolder->get(Textures::CHESS_WHITE);
    sf::IntRect textureRect(m_worldBounds);
    texture.setRepeated(true);
    std::unique_ptr<SpriteNode> background = { std::make_unique<SpriteNode>(RenderLayers::BACKGROUND, texture, textureRect, false) };
    m_sceneGraph.attachChild(std::move(background));
    //m_sceneLayers[Layers::BACKGROUND]->attachChild(std::move(background));
    /*
    std::unique_ptr<Warrior> wizard(new Warrior(RenderLayers::MAIN, 100, Textures::WIZARD, m_TextureHolder, m_SpriteSheetMapHolder));
    //SceneNode *wizardEnemyTmp = wizard.get();
    std::unique_ptr<CollisionShape> collisionShapeWizard(new CollisionCircle(12.f));
    wizard->setCollisionShape(std::move(collisionShapeWizard));
    //wizard->setPosition(800 / 2.f + 100.f, 480 / 2.f);
    wizard->setPosition(800 / 2.f - 60.f, 480 / 2.f - 10.f);
    wizard->setVelocity(60.f);
    wizard->setType(WorldObjectTypes::ENEMY);
    m_sceneGraph.attachChild(std::move(wizard));
    */

    // Warrior
    std::unique_ptr<Knight> warrior =
        { std::make_unique<Knight>(RenderLayers::MAIN, 100.f, Textures::KNIGHT, *m_context.textureHolder, *m_context.spriteSheetMapHolder, m_possibleTargetWarriors) };
    m_playerWarrior = warrior.get();
    std::unique_ptr<CollisionShape> collisionShapeWarrior = { std::make_unique<CollisionCircle>(12.f) };
    m_playerWarrior->setCollisionShape(std::move(collisionShapeWarrior));
    m_playerWarrior->setPosition(800 / 2.f, 480 / 2.f);
    m_playerWarrior->setVelocity(60.f);
    m_playerWarrior->setType(WorldObjectTypes::PLAYER | WorldObjectTypes::WARRIOR);
    //m_playerWarrior->setWeapon(swordPlayer.get());
    //m_playerWarrior->setBodyParts(playerLeftShoe.get(), playerRightShoe.get(), playerUpperBody.get());
    // Add Parts to player
    //m_playerWarrior->attachChild(std::move(swordPlayer));
    m_possibleTargetWarriors.push_back(warrior.get());
    m_sceneGraph.attachChild(std::move(warrior));


    std::unique_ptr<Warrior> enemy1 =
        { std::make_unique<Knight>(RenderLayers::MAIN, 100.f, Textures::KNIGHT, *m_context.textureHolder, *m_context.spriteSheetMapHolder, m_possibleTargetWarriors) };
    //SceneNode *wizardEnemyTmp = wizard.get();
    std::unique_ptr<CollisionShape> collisionShapeEnemy = { std::make_unique<CollisionCircle>(12.f) };
    enemy1->setCollisionShape(std::move(collisionShapeEnemy));
    //wizard->setPosition(800 / 2.f + 100.f, 480 / 2.f);
    enemy1->setPosition(800 / 2.f - 160.f, 480 / 2.f - 100.f);
    enemy1->setVelocity(60.f);
    enemy1->setType(WorldObjectTypes::ENEMY | WorldObjectTypes::WARRIOR);
    //enemy1->setActualTarget(m_playerWarrior);
    enemy1->setIsAiActive(false);
    m_possibleTargetWarriors.push_back(enemy1.get());
    m_sceneGraph.attachChild(std::move(enemy1));



    //m_sceneLayers[Layers::MAIN]->attachChild(std::move(warrior));
    //***********

    // Collision Tests
    /*
    if (m_playerWarrior->getCollisionShape()->isColliding(*wizardEnemyTmp->getCollisionShape()))
    {
        std::cout << "Colliding" << std::endl;
    }
    */
    //m_playerWarrior->getCollisionShape()->isColliding(*warriorEnemyTmp->getCollisionShape());
    std::cout << "MainGameScreen::buildScene End" << std::endl;

}

void MainGameScreen::safeSceneNodeTrasform()
{
    m_sceneGraph.safeTransform();
}

bool MainGameScreen::handleInput(Input input, float dt)
{
    switch (input.getInputType())
    {
        case InputTypes::CURSOR_POS :
        {
            m_commandQueue.push({ CommandTypes::LOOK_AT, WorldObjectTypes::PLAYER, input.getValues() });
            break;
        }
        case InputTypes::TRANSLATED_CURSOR_POS :
        {
            /*
            const sf::Vector2f UnitVecX(1.0, 0.f);
            // The angle which should be calculated have the coordinate systems midpoint at the center of the window,
            // so we have to use the translated mouse position so its relativ to the center of the window
            const sf::Vector2f TranslatedMousePos = { input.getValues() };
            const float Angle = { Calc::radToDeg(Calc::getVec2Angle<sf::Vector2f, sf::Vector2f>(UnitVecX, TranslatedMousePos)) };
            const float AngleSigned = TranslatedMousePos.y < 0.f ? -Angle : Angle;
            m_commandQueue.push({ CommandTypes::ROTATE, WorldObjectTypes::Player, { AngleSigned, 0.f } });
            */
            break;
        }
        case InputTypes::UP :
            m_commandQueue.push({ CommandTypes::MOVE_UP, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::DOWN :
            m_commandQueue.push({ CommandTypes::MOVE_DOWN, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::LEFT :
            m_commandQueue.push({ CommandTypes::MOVE_LEFT, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::RIGHT :
            m_commandQueue.push({ CommandTypes::MOVE_RIGHT, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::UP_LEFT :
            m_commandQueue.push({ CommandTypes::MOVE_UP_LEFT, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::UP_RIGHT :
            m_commandQueue.push({ CommandTypes::MOVE_UP_RIGHT, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::DOWN_LEFT :
            m_commandQueue.push({ CommandTypes::MOVE_DOWN_LEFT, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::DOWN_RIGHT :
            m_commandQueue.push({ CommandTypes::MOVE_DOWN_RIGHT, WorldObjectTypes::PLAYER });
            break;

        case InputTypes::LEFT_CLICK :
            m_commandQueue.push({ CommandTypes::ATTACK, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::RIGHT_CLICK_START :
            m_commandQueue.push({ CommandTypes::START_BLOCKING, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::RIGHT_CLICK_STOPED :
            m_commandQueue.push({ CommandTypes::STOP_BLOCKING, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::PAUSE :
            m_isGamePaused = !m_isGamePaused;
            if (m_isGamePaused)
            {
                m_screenStack->pushScreen(ScreenID::PAUSE);
            }
            else
            {
                // Remove pause screen
                m_screenStack->popScreen();
            }
            break;
        // Debug
        case InputTypes::D1 :

            break;
        case InputTypes::D2 :

            break;
        case InputTypes::D3 :
            m_showCollisionInfo = !m_showCollisionInfo;
            m_sceneGraph.changeCollisionShapeDraw(m_showCollisionInfo);
            break;
        case InputTypes::D4 :

            break;
        // Tmp (Arrow Keys)
        case InputTypes::UP_A :
            m_commandQueue.push({ CommandTypes::MOVE_UP, WorldObjectTypes::PLAYER_TWO });
            break;
        case InputTypes::DOWN_A :
            m_commandQueue.push({ CommandTypes::MOVE_DOWN, WorldObjectTypes::PLAYER_TWO });
            break;
        case InputTypes::LEFT_A :
            m_commandQueue.push({ CommandTypes::MOVE_LEFT, WorldObjectTypes::PLAYER_TWO });
            break;
        case InputTypes::RIGHT_A :
            m_commandQueue.push({ CommandTypes::MOVE_RIGHT, WorldObjectTypes::PLAYER_TWO });
            break;
        default:
            break;
    }
    /*
    if ( != m_lastMousePos)
    {
        commandQueue.push({ CommandTypes::ROTATE, WorldObjectTypes::Player, { AngleSigned, 0.f } });
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        commandQueue.push({ CommandTypes::MOVE_UP, WorldObjectTypes::Player });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        commandQueue.push({ CommandTypes::MOVE_DOWN, WorldObjectTypes::Player });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        commandQueue.push({ CommandTypes::MOVE_LEFT, WorldObjectTypes::Player });
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        commandQueue.push({ CommandTypes::MOVE_RIGHT, WorldObjectTypes::Player });
    }*/
    return false;
}

// Tmp (better implemention later)
/*
void World::controlWorldEntities()
{
    // Let Enemy look to player
    m_commandQueue.push({ CommandTypes::LOOK_AT, WorldObjectTypes::ENEMY, m_playerWarrior->getPosition() });
}
*/

void MainGameScreen::handleCommands(float dt)
{
    // Nothing to do when game is paused
    /*
    if (m_isGamePaused)
    {
        m_commandQueue.clear();
        return;
    }
    */
    while(!m_commandQueue.isEmpty())
    {
        m_sceneGraph.onCommand(m_commandQueue.pop(), dt);
    }
}

bool MainGameScreen::update(float dt)
{
     // Nothing to update when game is paused
    /*
    if (m_isGamePaused)
    {
        return;
    }
    */

    safeSceneNodeTrasform();
    handleCommands(dt);
    // Get iterator, pointing on the first element which should get erased
    auto destroyBegin = std::remove_if(m_possibleTargetWarriors.begin(), m_possibleTargetWarriors.end(), std::mem_fn(&Warrior::isMarkedForRemoval));
    // Remove the Warriors which are marked for removal
    m_possibleTargetWarriors.erase(destroyBegin, m_possibleTargetWarriors.end());

    // If player is not still in game we have to make the player pointer nullptr
    if (!isStillPlayerIsInGame())
    {
        m_playerWarrior = nullptr;
    }

    m_sceneGraph.removeDestroyed();
    m_sceneGraph.update(dt);

    handleCollision(dt);

    return false;
}

bool MainGameScreen::isStillPlayerIsInGame()
{
    // Check if player is still in container
    for (Warrior *warrior : m_possibleTargetWarriors)
    {
        if (warrior->getType() & WorldObjectTypes::PLAYER)
        {
            return true;
        }
    }
    return false;
}

void MainGameScreen::resolveEntityCollisions(SceneNode *sceneNodeFirst, SceneNode *sceneNodeSecond, CollisionInfo &collisionInfo)
{
    Entity *entityOne = { static_cast<Entity*>(sceneNodeFirst) };
    Entity *entityTwo = { static_cast<Entity*>(sceneNodeSecond) };
    float overlap = { collisionInfo.getLength() };
    entityOne->moveInDirection(collisionInfo.getResolveDirOfFirst(), overlap / 2.f);
    entityTwo->moveInDirection(collisionInfo.getResolveDirOfSecond(), overlap / 2.f);
    /*
    std::cout << "Player Enemy Enemy" << std::endl;
    std::cout << "OVERLAP: " << overlap << std::endl;
    std::cout << "DirOne: X:" << collisionInfo.getResolveDirOfFirst().x << " Y: " << collisionInfo.getResolveDirOfFirst().y << std::endl;
    std::cout << "DirTwo: X:" << collisionInfo.getResolveDirOfSecond().x <<  " Y: " << collisionInfo.getResolveDirOfSecond().y << std::endl;
    std::cout << "PosOne: X:" << entityOne->getWorldPosition().x << " Y: " << entityOne->getWorldPosition().y << std::endl;
    std::cout << "PosTwo: X:" << entityTwo->getWorldPosition().x <<  " Y: " << entityTwo->getWorldPosition().y << std::endl;
    */
}

void MainGameScreen::handleCollision(float dt)
{
    // Here are the collision information stored, which we use later and the affected SceneNodes
    std::vector<CollisionInfo> collisionData;

    m_sceneGraph.checkSceneCollision(m_sceneGraph, collisionData);
    for (CollisionInfo collisionInfo : collisionData)
    {
        SceneNode *sceneNodeFirst = { collisionInfo.getCollidedFirst() };
        SceneNode *sceneNodeSecond = { collisionInfo.getCollidedSecond() };
        SceneNode::Pair sceneNodes = { collisionInfo.getCollidedFirst(), collisionInfo.getCollidedSecond() };
        if (matchesCategories(sceneNodes, WorldObjectTypes::WARRIOR, WorldObjectTypes::WARRIOR))
        {
            resolveEntityCollisions(sceneNodeFirst, sceneNodeSecond, collisionInfo);
        }
        else if (matchesCategories(sceneNodes, WorldObjectTypes::WEAPON, WorldObjectTypes::WARRIOR))
        {
            Weapon *weapon = { static_cast<Weapon*>(getSceneNodeOfType(sceneNodes, WorldObjectTypes::WEAPON)) };
            Warrior *warrior = { static_cast<Warrior*>(getSceneNodeOfType(sceneNodes, WorldObjectTypes::WARRIOR)) };

            // Only damage warrior if the weapon is not its own
            // Alternative implementation for future (?): no collision check with parent nodes
            if (warrior->getWeapon() != weapon)
            {
                if (!warrior->isBlocking())
                {
                    warrior->damage(weapon->getTotalDamage());
                }
                else
                {
                    warrior->removeStanima(weapon->getTotalDamage());
                }
                // To prevent multiple damage, turn off collison check
                weapon->setIsCollisionCheckOn(false);
            }
        }
        if (m_showCollisionInfo)
        {
            //std::cout << "Collision: " << colCnt++ << std::endl;
        }

    }
}
/*
bool World::matchesCategories(SceneNode::Pair &colliders, WorldObjectTypes worldObjectType1, WorldObjectTypes worldObjectType2)
{
    unsigned int category1 = static_cast<unsigned int>(colliders.first->getType());
    unsigned int category2 = static_cast<unsigned int>(colliders.second->getType());
    unsigned int type1 = static_cast<unsigned int>(worldObjectType1);
    unsigned int type2 = static_cast<unsigned int>(worldObjectType2);
    std::cout << "Cat1: " << category1 << " Cat2: " << category2 << " Type1: " << type1 << " Type2: " << type2 << std::endl;
    if (type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if (type1 & category2 && type2 & category1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    return false;
}
*/

SceneNode* MainGameScreen::getSceneNodeOfType(SceneNode::Pair sceneNodePair, WorldObjectTypes type)
{
    SceneNode *sceneNodeOne = sceneNodePair.first;
    SceneNode *sceneNodeTwo = sceneNodePair.second;
    if (sceneNodeOne->getType() & type)
    {
        return sceneNodeOne;
    }
    else if (sceneNodeTwo->getType() & type)
    {
        return sceneNodeTwo;
    }
    return nullptr;
}

bool MainGameScreen::matchesCategories(SceneNode::Pair &colliders, unsigned int type1, unsigned int type2)
{
    unsigned int category1 = colliders.first->getType();
    unsigned int category2 = colliders.second->getType();

    //std::cout << "Cat1: " << category1 << " Cat2: " << category2 << " Type1: " << type1 << " Type2: " << type2 << std::endl;
    if (type1 & category1 && type2 & category2)
    {
        return true;
    }
    else if (type1 & category2 && type2 & category1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    return false;
}

void MainGameScreen::render()
{
    if (m_playerWarrior)
    {
        std::cout << "Players Stamina: " << m_playerWarrior->getCurrentStanima() << std::endl;
    }
    else
    {
        std::cout << "Players is null" << std::endl;
    }
    if (m_isGamePaused && sf::Shader::isAvailable())
    {
        m_context.window->draw(m_renderManager, &m_context.shaderHolder->get(Shaders::GRAYSCALE));
    }
    else
    {
        m_context.window->draw(m_renderManager);
    }
    //m_context.window->draw(circleShape, &m_shader);


}

