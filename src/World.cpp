#include "World.hpp"
#include "Collision/CollisionShape.hpp"
#include "Collision/CollisionCircle.hpp"
#include "Collision/CollisionRect.hpp"
#include "Components/SpriteNode.hpp"
#include "Components/Warrior.hpp"
#include "Components/Weapon.hpp"
#include "Components/Knight.hpp"
#include "Calc.hpp"
#include <memory>

World::World(const bool isInDebug, sf::RenderWindow *window, const ResourceHolder<sf::Font, Fonts> &FontHolder,
const ResourceHolder<sf::Texture, Textures> &TextureHolder, const SpriteSheetMapHolder &spriteSheetMapHolder)
: m_isInDebug { isInDebug }
, m_showCollisionInfo{ false }
, m_window{ window }
, m_worldView{ m_window->getDefaultView() }
, m_renderManager{ &m_sceneGraph }
, m_FontHolder{ FontHolder }
, m_TextureHolder{ TextureHolder }
, m_SpriteSheetMapHolder{ spriteSheetMapHolder }
//, m_inputQueue{inputQueue}
, m_worldBounds{ 0.f, 0.f, 800.f, 480.f }
, m_playerWarrior{ nullptr }
{

}

void World::buildScene()
{
    std::cout << "World::buildScene" << std::endl;
    /*
    for (std::size_t i = { 0 }; i < Layers::COUNT; i++)
    {
        // Use std::unique_ptr<SceneNode>
        SceneNode::Ptr layer(new SceneNode());
        m_sceneLayers[i] = layer.get();
        m_sceneGraph.attachChild(std::move(layer));
    }
    */

    sf::Texture &texture = m_TextureHolder.get(Textures::CHESS_WHITE);
    sf::IntRect textureRect(m_worldBounds);
    texture.setRepeated(true);
    std::unique_ptr<SpriteNode> background(new SpriteNode(RenderLayers::BACKGROUND, texture, textureRect, false));
    m_sceneGraph.attachChild(std::move(background));
    //m_sceneLayers[Layers::BACKGROUND]->attachChild(std::move(background));

    /*
    std::unique_ptr<Warrior> wizard(new Warrior(100, Textures::WIZARD, m_TextureHolder));
    SceneNode *wizardEnemyTmp = wizard.get();
    std::unique_ptr<CollisionShape> collisionShapeWizard(new CollisionCircle(12.f , &m_drawCollisionShape));
    wizard->setCollisionShape(std::move(collisionShapeWizard));
    //wizard->setPosition(800 / 2.f + 100.f, 480 / 2.f);
    wizard->setPosition(800 / 2.f - 60.f, 480 / 2.f - 10.f);
    wizard->setVelocity(30.f, 30.f);
    wizard->setType(WorldObjectTypes::ENEMY);
    m_sceneLayers[Layers::MAIN]->attachChild(std::move(wizard));


    std::unique_ptr<Warrior> warriorEnemy(new Warrior(100, Textures::KNIGHT, m_TextureHolder));
    SceneNode *warriorEnemyTmp = warriorEnemy.get();
    std::unique_ptr<CollisionShape> collisionShapeWarriorEnemy(new CollisionRect({ 32.f, 32.f }, &m_drawCollisionShape));
    warriorEnemy->setCollisionShape(std::move(collisionShapeWarriorEnemy));
    warriorEnemy->setPosition(800 / 3.f + 100.f, 480 / 3.f);
    warriorEnemy->setVelocity(30.f, 30.f);
    warriorEnemy->setType(WorldObjectTypes::ENEMY);
    m_sceneLayers[Layers::MAIN]->attachChild(std::move(warriorEnemy));


    std::unique_ptr<Warrior> warriorEnemy2(new Warrior(100, Textures::KNIGHT, m_TextureHolder));
    SceneNode *warriorEnemy2Tmp = warriorEnemy2.get();
    std::unique_ptr<CollisionShape> collisionShapeWarriorEnemy2(new CollisionRect({ 32.f, 32.f }, &m_drawCollisionShape));
    warriorEnemy2->setCollisionShape(std::move(collisionShapeWarriorEnemy2));
    warriorEnemy2->setPosition(800 / 3.f + 300.f, 480 / 3.f);
    warriorEnemy2->setVelocity(30.f, 30.f);
    warriorEnemy2->setType(WorldObjectTypes::NONE);
    m_sceneLayers[Layers::MAIN]->attachChild(std::move(warriorEnemy2));

    std::unique_ptr<Warrior> warriorEnemy3(new Warrior(100, Textures::KNIGHT, m_TextureHolder));
    SceneNode *warriorEnemy3Tmp = warriorEnemy3.get();
    std::unique_ptr<CollisionShape> collisionShapeWarriorEnemy3(new CollisionRect({ 32.f, 32.f }, &m_drawCollisionShape));
    warriorEnemy3->setCollisionShape(std::move(collisionShapeWarriorEnemy3));
    warriorEnemy3->setPosition(800 / 3.f + 300.f, 380);
    warriorEnemy3->setVelocity(30.f, 30.f);
    warriorEnemy3->setType(WorldObjectTypes::NONE);
    warriorEnemy3->setRotation(50.f);
    m_sceneLayers[Layers::MAIN]->attachChild(std::move(warriorEnemy3));
    // ******* PLAYER *********
    // SWORD
    std::unique_ptr<Weapon> swordPlayer(new Weapon(60 ,Textures::SWORD, m_TextureHolder));
    swordPlayer->setType(WorldObjectTypes::WEAPON);
    swordPlayer->setPosition(0.f, 0.f);
    //swordPlayer->setRotationPoint(0.f, swordPlayer->getSpriteHeight() / 2.f);
    swordPlayer->setEquipPoint(-10.f, 0.f);
    std::unique_ptr<CollisionShape> collisionShapePlayerSword(new CollisionRect({ swordPlayer->getSpriteWidth(), swordPlayer->getSpriteHeight() }, &m_drawCollisionShape));
    swordPlayer->setCollisionShape(std::move(collisionShapePlayerSword));
    // Parts
    std::unique_ptr<SpriteNode> playerLeftShoe(new SpriteNode(m_TextureHolder.get(Textures::KNIGHT_LEFT_SHOE), true));
    playerLeftShoe->setPosition(8.f, -5.f);
    std::unique_ptr<SpriteNode> playerRightShoe(new SpriteNode(m_TextureHolder.get(Textures::KNIGHT_RIGHT_SHOE), true));
    playerRightShoe->setPosition(8.f, 5.f);
    std::unique_ptr<SpriteNode> playerUpperBody(new SpriteNode(m_TextureHolder.get(Textures::KNIGHT_UPPER_BODY), true));

    // Warrior
    std::unique_ptr<Knight> warrior(new Knight(100, Textures::KNIGHT, m_TextureHolder));
    m_playerWarrior = warrior.get();
    std::unique_ptr<CollisionShape> collisionShapeWarrior(new CollisionCircle(12.f, &m_drawCollisionShape));
    //std::unique_ptr<CollisionShape> collisionShapeWarrior(new CollisionRect({ 32.f, 32.f }));
    m_playerWarrior->setCollisionShape(std::move(collisionShapeWarrior));
    m_playerWarrior->setPosition(800 / 2.f, 480 / 2.f);
    m_playerWarrior->setVelocity(60.f, 60.f);
    m_playerWarrior->setType(WorldObjectTypes::PLAYER);
    m_playerWarrior->setWeapon(swordPlayer.get());
    m_playerWarrior->setBodyParts(playerLeftShoe.get(), playerRightShoe.get(), playerUpperBody.get());
    // Add Parts to player
    m_playerWarrior->attachChild(std::move(playerLeftShoe));
    m_playerWarrior->attachChild(std::move(playerRightShoe));
    m_playerWarrior->attachChild(std::move(swordPlayer));
    m_playerWarrior->attachChild(std::move(playerUpperBody));
    m_sceneLayers[Layers::MAIN]->attachChild(std::move(warrior));
    //***********



    std::unique_ptr<Warrior> warriorPlayerTwo(new Warrior(100, Textures::KNIGHT, m_TextureHolder));
    Warrior *playerWarriorTwo = warriorPlayerTwo.get();
    //std::unique_ptr<CollisionShape> collisionShapeWarriorPlayer2(new CollisionCircle(12.f));
    std::unique_ptr<CollisionShape> collisionShapeWarriorPlayer2(new CollisionRect({ 32.f, 32.f }, &m_drawCollisionShape));
    playerWarriorTwo->setCollisionShape(std::move(collisionShapeWarriorPlayer2));
    playerWarriorTwo->setPosition(800 / 2.f - 160.f, 480 / 2.f + 90.f);
    playerWarriorTwo->setVelocity(60.f, 60.f);
    playerWarriorTwo->setType(WorldObjectTypes::PLAYER_TWO);
    m_sceneLayers[Layers::MAIN]->attachChild(std::move(warriorPlayerTwo));
    */

    std::unique_ptr<Warrior> wizard(new Warrior(RenderLayers::MAIN, 100, Textures::WIZARD, m_TextureHolder, m_SpriteSheetMapHolder));
    SceneNode *wizardEnemyTmp = wizard.get();
    std::unique_ptr<CollisionShape> collisionShapeWizard(new CollisionCircle(12.f));
    wizard->setCollisionShape(std::move(collisionShapeWizard));
    //wizard->setPosition(800 / 2.f + 100.f, 480 / 2.f);
    wizard->setPosition(800 / 2.f - 60.f, 480 / 2.f - 10.f);
    wizard->setVelocity(30.f, 30.f);
    wizard->setType(WorldObjectTypes::ENEMY);
    m_sceneGraph.attachChild(std::move(wizard));


    // ******* PLAYER *********
    // SWORD
    /*
    std::unique_ptr<Weapon> swordPlayer(new Weapon(RenderLayers::WEAPON, 60 ,Textures::SWORD, m_TextureHolder));
    swordPlayer->setType(WorldObjectTypes::WEAPON);
    swordPlayer->setPosition(0.f, 0.f);
    //swordPlayer->setRotationPoint(0.f, swordPlayer->getSpriteHeight() / 2.f);
    swordPlayer->setEquipPoint(-10.f, 0.f);
    std::unique_ptr<CollisionShape> collisionShapePlayerSword(new CollisionRect({ swordPlayer->getSpriteWidth(), swordPlayer->getSpriteHeight() }, &m_drawCollisionShape));
    swordPlayer->setCollisionShape(std::move(collisionShapePlayerSword));
    */
    // Warrior
    std::unique_ptr<Knight> warrior(new Knight(RenderLayers::MAIN, 100, Textures::KNIGHT, m_TextureHolder, m_SpriteSheetMapHolder));
    m_playerWarrior = warrior.get();
    std::unique_ptr<CollisionShape> collisionShapeWarrior(new CollisionCircle(12.f));
    //std::unique_ptr<CollisionShape> collisionShapeWarrior(new CollisionRect({ 32.f, 32.f }));
    m_playerWarrior->setCollisionShape(std::move(collisionShapeWarrior));
    m_playerWarrior->setPosition(800 / 2.f, 480 / 2.f);
    m_playerWarrior->setVelocity(60.f, 60.f);
    m_playerWarrior->setType(WorldObjectTypes::PLAYER);
    //m_playerWarrior->setWeapon(swordPlayer.get());
    //m_playerWarrior->setBodyParts(playerLeftShoe.get(), playerRightShoe.get(), playerUpperBody.get());
    // Add Parts to player
    //m_playerWarrior->attachChild(std::move(swordPlayer));
    m_sceneGraph.attachChild(std::move(warrior));
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
    std::cout << "World::buildScene End" << std::endl;
}

void World::safeSceneNodeTrasform()
{
    m_sceneGraph.safeTransform();
}

void World::translateInput(Input input, float dt)
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
        case InputTypes::LEFT_CLICK :
            m_commandQueue.push({ CommandTypes::ATTACK, WorldObjectTypes::PLAYER });
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
}

// Tmp (better implemention later)
void World::controlWorldEntities()
{
    // Let Enemy look to player
    m_commandQueue.push({ CommandTypes::LOOK_AT, WorldObjectTypes::ENEMY, m_playerWarrior->getPosition() });
}

void World::handleCommands(float dt)
{
    while(!m_commandQueue.isEmpty())
    {
        m_sceneGraph.onCommand(m_commandQueue.pop(), dt);
    }
}

void World::update(float dt)
{
    m_sceneGraph.removeDestroyed();
    m_sceneGraph.update(dt);
}

void World::resolveEntityCollisions(SceneNode *sceneNodeFirst, SceneNode *sceneNodeSecond, CollisionInfo &collisionInfo)
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

void World::handleCollision(float dt)
{
    // Here are the collision information stored, which we use later and the affected SceneNodes
    std::vector<CollisionInfo> collisionData;

    m_sceneGraph.checkSceneCollision(m_sceneGraph, collisionData);
    for (CollisionInfo collisionInfo : collisionData)
    {
        SceneNode *sceneNodeFirst = { collisionInfo.getCollidedFirst() };
        SceneNode *sceneNodeSecond = { collisionInfo.getCollidedSecond() };
        SceneNode::Pair sceneNodes = { collisionInfo.getCollidedFirst(), collisionInfo.getCollidedSecond() };
        if (matchesCategories(sceneNodes, WorldObjectTypes::PLAYER, WorldObjectTypes::ENEMY))
        {
            resolveEntityCollisions(sceneNodeFirst, sceneNodeSecond, collisionInfo);
        }
        else if (matchesCategories(sceneNodes, WorldObjectTypes::ENEMY, WorldObjectTypes::ENEMY))
        {
            resolveEntityCollisions(sceneNodeFirst, sceneNodeSecond, collisionInfo);
        }
        else if (matchesCategories(sceneNodes, WorldObjectTypes::PLAYER, WorldObjectTypes::PLAYER_TWO))
        {
            resolveEntityCollisions(sceneNodeFirst, sceneNodeSecond, collisionInfo);
        }
        else if (matchesCategories(sceneNodes, WorldObjectTypes::ENEMY, WorldObjectTypes::PLAYER_TWO))
        {
            resolveEntityCollisions(sceneNodeFirst, sceneNodeSecond, collisionInfo);
            //pairTmp.first->restoreLastTransform();
            //pairTmp.second->restoreLastTransform();
        }
        else if (matchesCategories(sceneNodes, WorldObjectTypes::NONE, WorldObjectTypes::PLAYER))
        {
            resolveEntityCollisions(sceneNodeFirst, sceneNodeSecond, collisionInfo);
            //pairTmp.first->restoreLastTransform();
            //pairTmp.second->restoreLastTransform();
        }
        else if (matchesCategories(sceneNodes, WorldObjectTypes::WEAPON, WorldObjectTypes::ENEMY))
        {
            std::cout << "WEAPON collision" << std::endl;
            Weapon *weapon = { static_cast<Weapon*>(getSceneNodeOfType(sceneNodes, WorldObjectTypes::WEAPON)) };
            Warrior *warrior = { static_cast<Warrior*>(getSceneNodeOfType(sceneNodes, WorldObjectTypes::ENEMY)) };
            warrior->damage(weapon->getDamage());
            // To prevent multiple damage, turn off collison check
            weapon->setIsCollisionCheckOn(false);
            std::cout << "Rest health: " << warrior->getCurrentHealth() << std::endl;
        }
        if (m_showCollisionInfo)
        {
            std::cout << "Collision: " << colCnt++ << std::endl;
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

SceneNode* World::getSceneNodeOfType(SceneNode::Pair sceneNodePair, WorldObjectTypes type)
{
    SceneNode *sceneNodeOne = sceneNodePair.first;
    SceneNode *sceneNodeTwo = sceneNodePair.second;
    if (sceneNodeOne->getType() == type)
    {
        return sceneNodeOne;
    }
    else if (sceneNodeTwo->getType() == type)
    {
        return sceneNodeTwo;
    }
    return nullptr;
}

bool World::matchesCategories(SceneNode::Pair &colliders, WorldObjectTypes type1, WorldObjectTypes type2)
{
    WorldObjectTypes category1 = colliders.first->getType();
    WorldObjectTypes category2 = colliders.second->getType();

    //std::cout << "Cat1: " << category1 << " Cat2: " << category2 << " Type1: " << type1 << " Type2: " << type2 << std::endl;
    if (type1 == category1 && type2 == category2)
    {
        return true;
    }
    else if (type1 == category2 && type2 == category1)
    {
        std::swap(colliders.first, colliders.second);
        return true;
    }
    return false;
}

void World::render()
{
    //std::cout << "Render" << std::endl;
    //m_window->clear();
    m_window->draw(m_renderManager);
    //m_window->display();
}

