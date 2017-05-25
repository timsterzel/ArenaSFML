#include "Screens/MainGameScreen.hpp"
#include "Collision/CollisionShape.hpp"
#include "Collision/CollisionCircle.hpp"
#include "Collision/CollisionRect.hpp"
#include "Components/Item.hpp"
#include "Components/SpriteNode.hpp"
#include "Components/Warrior.hpp"
#include "Components/Weapon.hpp"
#include "Components/Knight.hpp"
#include "Components/Runner.hpp"
#include "Components/Wizard.hpp"
#include "Calc.hpp"
#include "Helpers.hpp"
#include <memory>
#include "Game.hpp"
#include <cmath>

MainGameScreen::MainGameScreen(ScreenStack *screenStack, Context &context, 
        const Level &level)
: Screen(screenStack, context)
, m_isGamePaused{ false }
, m_showCollisionInfo{ false }
, m_window{ *context.window }
, m_level{ level }
, m_isRenderTextureAvailable{ false }
, m_gameView{ context.gameView }
, m_guiView{ context.guiView }
, m_guiEnvironment{ *context.window }
, m_healthBarWarr1{ nullptr }
, m_healthBarWarr2{ nullptr }
, m_stanimaBarWarr1{ nullptr }
, m_stanimaBarWarr2{ nullptr }
, m_background{ sf::Vector2f{ 10000.f, 10000.f} }
, m_currentBgColorStep{ 0 }
, m_totalBgStepTime{ 5.f }
, m_currentBgStepTime{ 0.f }
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
    if(!m_renderTexture.create(m_window.getSize().x, 
                m_window.getSize().y))
    {
        std::cout << "Error by creating RenderTexture \n";
        m_isRenderTextureAvailable = false;
    }
    else
    {
        m_isRenderTextureAvailable = true;
    }
    // healt bar
    gsf::ProgressWidget::Ptr healthWar1{ gsf::ProgressWidget::create(100.f, 20.f) };
    m_healthBarWarr1 = healthWar1.get();
    healthWar1->setProgressColor(sf::Color::Red);
    m_guiEnvironment.addWidget(std::move(healthWar1));

    gsf::ProgressWidget::Ptr healthWar2{ gsf::ProgressWidget::create(100.f, 20.f) };
    m_healthBarWarr2 = healthWar2.get();
    healthWar2->setProgressColor(sf::Color::Red);
    m_guiEnvironment.addWidget(std::move(healthWar2));
    
    // Stanima bar
    gsf::ProgressWidget::Ptr stanimaWar1{ gsf::ProgressWidget::create(100.f, 20.f) };
    m_stanimaBarWarr1 = stanimaWar1.get();
    stanimaWar1->setProgressColor(sf::Color::Blue);
    m_guiEnvironment.addWidget(std::move(stanimaWar1));
    
    gsf::ProgressWidget::Ptr stanimaWar2{ 
        gsf::ProgressWidget::create(100.f, 20.f) };
    m_stanimaBarWarr2 = stanimaWar2.get();
    stanimaWar2->setProgressColor(sf::Color::Blue);
    m_guiEnvironment.addWidget(std::move(stanimaWar2));
    
    // Create Console widget
    gsf::ConsoleWidget::Ptr consoleWidget{ gsf::ConsoleWidget::create(
            getContext().fontHolder->get("default")) };
    consoleWidget->setIsVisible(false);
    consoleWidget->setBackgroundColor(sf::Color(255, 255, 255, 128));
    m_consoleWidget = consoleWidget.get();
    m_consoleWidget->setOnCommandEnteredListener(
            [this](gsf::Widget *widget, sf::String command)
            {
                this->handleConsoleCommands(widget, command);
            });
    
    m_guiEnvironment.addWidget(std::move(consoleWidget));
    // Calculate the pos and size of the gui widget depending of the views
    calcGuiSizeAndPos();
    // Play music
    m_context.music->play("gametheme01");
    
    /*
    for (std::size_t i = { 0 }; i < Layers::COUNT; i++)
    {
        // Use std::unique_ptr<SceneNode>
        SceneNode::Ptr layer(new SceneNode());
        m_sceneLayers[i] = layer.get();
        m_sceneGraph.attachChild(std::move(layer));
    }
    */
    

    // Background
    m_background.setOrigin(m_background.getSize().x / 2.f, 
            m_background.getSize().y / 2.f);
	// The colors
	std::vector<sf::Color> colors {
		sf::Color(170, 255, 1, 255), // Green
		sf::Color(255, 170, 1, 255), // Orange
		sf::Color(255, 0, 170, 255), // Red
		sf::Color(170, 0, 255, 255), // Violet
		//sf::Color(0, 170, 255, 255)  // Blue
		sf::Color(12, 39, 146, 255)  // Blue
	};
	// The colors from which to which is interpoled
	m_bgColorSteps = {
		{ colors[0] , colors[1] }, // Green -> Orange
		{ colors[1] , colors[2] }, // Orange -> Red
		{ colors[2] , colors[3] }, // Red -> Violet
		{ colors[3] , colors[4] }, // Violet -> Blue
		{ colors[4] , colors[0] }, // Blue -> Green
	};
    
    /*
    sf::Texture &texture = m_context.textureHolder->get(Textures::CHESS_WHITE);
    sf::IntRect textureRect(m_worldBounds);
    texture.setRepeated(true);
    std::unique_ptr<SpriteNode> background{ std::make_unique<SpriteNode>
        (RenderLayers::BACKGROUND, texture, textureRect, false) };
    m_sceneGraph.attachChild(std::move(background));
    */

    // Warrior
    std::unique_ptr<Wizard> warrior{ std::make_unique<Wizard>
        (RenderLayers::MAIN, 100.f, "wizard", *m_context.textureHolder, 
         *m_context.spriteSheetMapHolder, m_possibleTargetWarriors) };
    
    //std::unique_ptr<Knight> warrior{ std::make_unique<Knight>
    //    (RenderLayers::MAIN, 100.f, Textures::KNIGHT, *m_context.textureHolder, 
    //     *m_context.spriteSheetMapHolder, m_possibleTargetWarriors) };
    
    //std::unique_ptr<Runner> warrior{ std::make_unique<Runner>
    //    (RenderLayers::MAIN, 100.f, Textures::RUNNER, *m_context.textureHolder, 
    //     *m_context.spriteSheetMapHolder, m_possibleTargetWarriors) };
    m_playerWarrior = warrior.get();
    std::unique_ptr<CollisionShape> collisionShapeWarrior{ 
        std::make_unique<CollisionCircle>(12.f) };
    m_playerWarrior->setCollisionShape(std::move(collisionShapeWarrior));
    m_playerWarrior->setPosition(800 / 2.f, 480 / 2.f);
    //m_playerWarrior->setVelocity(60.f);
    m_playerWarrior->setType(
            WorldObjectTypes::PLAYER | 
            WorldObjectTypes::WARRIOR | 
            WorldObjectTypes::KNIGHT);
    //m_playerWarrior->setWeapon(swordPlayer.get());
    //m_playerWarrior->setBodyParts(playerLeftShoe.get(), playerRightShoe.get(), playerUpperBody.get());
    // Add Parts to player
    //m_playerWarrior->attachChild(std::move(swordPlayer));
    m_possibleTargetWarriors.push_back(warrior.get());
    m_sceneGraph.attachChild(std::move(warrior));

    // Enemy
    std::unique_ptr<Warrior> enemy1{ std::make_unique<Runner>
        (RenderLayers::MAIN, 100.f, "runner", *m_context.textureHolder, 
         *m_context.spriteSheetMapHolder, m_possibleTargetWarriors) };
    //SceneNode *wizardEnemyTmp = wizard.get();
    std::unique_ptr<CollisionShape> collisionShapeEnemy{ 
        std::make_unique<CollisionCircle>(12.f) };
    enemy1->setCollisionShape(std::move(collisionShapeEnemy));
    //wizard->setPosition(800 / 2.f + 100.f, 480 / 2.f);
    enemy1->setPosition(800 / 2.f - 160.f, 480 / 2.f - 100.f);
    //enemy1->setVelocity(60.f);
    enemy1->setType(WorldObjectTypes::ENEMY | 
            WorldObjectTypes::WARRIOR |
            WorldObjectTypes::RUNNER);
    //enemy1->setActualTarget(m_playerWarrior);
    enemy1->setIsAiActive(false);
    m_possibleTargetWarriors.push_back(enemy1.get());
    m_sceneGraph.attachChild(std::move(enemy1));
    
    buildLevel();
}

void MainGameScreen::buildLevel()
{
    // Load the tiles
    for (const Level::TileData &tile : m_level.tiles)
    {
        //*m_context.textureHolder
        sf::Texture &texture{ m_context.textureHolder->get("level") };
        sf::IntRect textureRect{ m_context.spriteSheetMapHolder->getRectData(
                "level", tile.id) };
        std::cout << "TileId: " << tile.id << "\n";
        std::unique_ptr<SpriteNode> sprite{ 
            std::make_unique<SpriteNode>(
                    RenderLayers::BACKGROUND, texture, textureRect, false) };
        sprite->setOrigin(
                sprite->getSpriteWidth() / 2.f, sprite->getSpriteHeight() /2.f);
        sprite->setPosition(tile.position);
        if (tile.isCollisionOn)
        {
            sf::Vector2f size{ 
                sprite->getSpriteWidth(), sprite->getSpriteHeight() };
            std::unique_ptr<CollisionRect> collision{ 
                std::make_unique<CollisionRect>(size) };
            // Adjust pos so that the collision shape is in the center of the 
            // centered object
            collision->setPosition(size.x / 2.f, size.y / 2.f);
            sprite->setCollisionShape(std::move(collision));
        }
        sprite->setType(WorldObjectTypes::LEVEL);
        m_sceneGraph.attachChild(std::move(sprite));
    }
    // Load spawn points
    if (m_level.spawnPoint1)
    {
        std::cout << "SpawnPoint1 x: " << m_level.spawnPoint1->position.x
            << " y: " << m_level.spawnPoint1->position.y << std::endl;
        m_playerWarrior->setPosition(m_level.spawnPoint1->position);
    }
    if (m_level.spawnPoint2)
    {
        if (m_possibleTargetWarriors.size() > 1)
        {
            std::cout << "Larger \n";
            m_possibleTargetWarriors[1]->setPosition(
                    m_level.spawnPoint2->position);
        }
    }
}

void MainGameScreen::handleConsoleCommands(gsf::Widget* widget, sf::String command)
{
    std::string commandUpper{ Helpers::toUpper(command) };
    std::vector<std::string> commands{ Helpers::splitString(commandUpper, ' ') };
    for (const std::string &str : commands)
    {
        std::cout << "Command: " << str << "\n";
    }
    std::size_t comCnt{ commands.size() };
    // No commands so nothing to do
    if (comCnt < 1)
    {
        return;
    }
    std::string mainCom{ commands[0] };
    // Spawm something
    if (mainCom == "SPAWN")
    {
        // Nothing to spawn specified
        if (comCnt < 2)
        {
            return;
        }
        std::unique_ptr<Warrior> spawnWar{ nullptr };
        std::string spawnObjCom{ commands[1] };
        WorldObjectTypes type;
        if (spawnObjCom == "KNIGHT")
        {
            spawnWar = std::make_unique<Knight>
                (RenderLayers::MAIN, 100.f, "knight", *m_context.textureHolder, 
                *m_context.spriteSheetMapHolder, m_possibleTargetWarriors);
            type = WorldObjectTypes::KNIGHT;
        }
        else if (spawnObjCom == "RUNNER")
        {
            spawnWar = std::make_unique<Runner>
                (RenderLayers::MAIN, 100.f, "runner", *m_context.textureHolder, 
                *m_context.spriteSheetMapHolder, m_possibleTargetWarriors);
            type = WorldObjectTypes::RUNNER;
        }
        // If spawnWar is null there was no valid warrior specified, so nothing to do
        if (!spawnWar)
        {
            return;
        }
        std::unique_ptr<CollisionShape> collisionShapeEnemy{ 
            std::make_unique<CollisionCircle>(12.f) };
        spawnWar->setCollisionShape(std::move(collisionShapeEnemy));
        spawnWar->setPosition(800.f / 2, 400.f / 2.f);
        //spawnWar->setVelocity(60.f);
        spawnWar->setType(WorldObjectTypes::ENEMY | 
            WorldObjectTypes::WARRIOR |
            type);
        spawnWar->setIsAiActive(true);
        m_possibleTargetWarriors.push_back(spawnWar.get());
        m_sceneGraph.attachChild(std::move(spawnWar));
    }
    else if (mainCom == "HEAL")
    {
        if (comCnt > 1)
        {
            try 
            {
                float val{ std::stof(commands[1]) };
                if (m_playerWarrior)
                {
                    m_playerWarrior->heal(val);
                }
            } 
            catch (...)
            {
                m_consoleWidget->addTextToDisplay(
                        "No valid value as second parameter");
            }
        }
    }
    else if (mainCom == "DAMAGE")
    {
        if (comCnt > 1)
        {
            try 
            {
                float val{ std::stof(commands[1]) };
                if (m_playerWarrior)
                {
                    m_playerWarrior->damage(val);
                }
            } 
            catch (...)
            {
                m_consoleWidget->addTextToDisplay(
                        "No valid value as second parameter");
            }
        }
    }
};

void MainGameScreen::safeSceneNodeTrasform()
{
    m_sceneGraph.safeTransform();
}

bool MainGameScreen::handleInput(Input &input, float dt)
{
    switch (input.getInputType())
    {
        case InputTypes::CURSOR_POS :
        {
            m_commandQueue.push({ CommandTypes::LOOK_AT, WorldObjectTypes::PLAYER, 
                    input.getValues() });
            break;
        }
        case InputTypes::TRANSLATED_CURSOR_POS :
        {
            /*
            const sf::Vector2f UnitVecX(1.0, 0.f);
            // The angle which should be calculated have the coordinate systems 
            // midpoint at the center of the window,
            // so we have to use the translated mouse position so its relativ to 
            // the center of the window
            const sf::Vector2f TranslatedMousePos = { input.getValues() };
            const float Angle{ Calc::radToDeg(
                Calc::getVec2Angle<sf::Vector2f, sf::Vector2f>
                    (UnitVecX, TranslatedMousePos)) };
            const float AngleSigned = TranslatedMousePos.y < 0.f ? -Angle : Angle;
            m_commandQueue.push({ CommandTypes::ROTATE, WorldObjectTypes::Player, 
                { AngleSigned, 0.f } });
            */
            break;
        }
        case InputTypes::UP :
            m_commandQueue.push({ CommandTypes::MOVE_UP, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::DOWN :
            m_commandQueue.push(
                    { CommandTypes::MOVE_DOWN, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::LEFT :
            m_commandQueue.push(
                    { CommandTypes::MOVE_LEFT, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::RIGHT :
            m_commandQueue.push(
                    { CommandTypes::MOVE_RIGHT, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::UP_LEFT :
            m_commandQueue.push(
                    { CommandTypes::MOVE_UP_LEFT, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::UP_RIGHT :
            m_commandQueue.push(
                    { CommandTypes::MOVE_UP_RIGHT, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::DOWN_LEFT :
            m_commandQueue.push(
                    { CommandTypes::MOVE_DOWN_LEFT, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::DOWN_RIGHT :
            m_commandQueue.push(
                    { CommandTypes::MOVE_DOWN_RIGHT, WorldObjectTypes::PLAYER });
            break;

        case InputTypes::LEFT_CLICK :
            m_commandQueue.push(
                    { CommandTypes::ACTION1, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::LCONTROL_LEFT_CLICK :
            m_commandQueue.push(
                    { CommandTypes::ACTION2, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::RIGHT_CLICK :
            m_commandQueue.push(
                    { CommandTypes::ACTION3, WorldObjectTypes::PLAYER });
            
        case InputTypes::RIGHT_CLICK_START :
            m_commandQueue.push(
                    { CommandTypes::START_BLOCKING, WorldObjectTypes::PLAYER });
            break;
        case InputTypes::RIGHT_CLICK_STOPED :
            m_commandQueue.push(
                    { CommandTypes::STOP_BLOCKING, WorldObjectTypes::PLAYER });
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
            
        case InputTypes::CONSOLE :
            m_consoleWidget->setIsVisible(!m_consoleWidget->isVisible());
            break;
        // Tmp (Arrow Keys)
        case InputTypes::UP_A :
            m_commandQueue.push(
                    { CommandTypes::MOVE_UP, WorldObjectTypes::PLAYER_TWO });
            break;
        case InputTypes::DOWN_A :
            m_commandQueue.push(
                    { CommandTypes::MOVE_DOWN, WorldObjectTypes::PLAYER_TWO });
            break;
        case InputTypes::LEFT_A :
            m_commandQueue.push(
                    { CommandTypes::MOVE_LEFT, WorldObjectTypes::PLAYER_TWO });
            break;
        case InputTypes::RIGHT_A :
            m_commandQueue.push(
                    { CommandTypes::MOVE_RIGHT, WorldObjectTypes::PLAYER_TWO });
            break;
        default:
            break;
    }
    /*
    if ( != m_lastMousePos)
    {
        commandQueue.push(
            { CommandTypes::ROTATE, WorldObjectTypes::Player, 
                { AngleSigned, 0.f } });
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

bool MainGameScreen::handleEvent(sf::Event &event, float dt)
{
    m_window.setView(m_guiView);
    return !m_guiEnvironment.handleEvent(event);
    m_window.setView(m_gameView);
}
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
    updateBackground(dt);

    safeSceneNodeTrasform();
    handleCommands(dt);
    // Get iterator, pointing on the first element which should get erased
    auto destroyBegin = std::remove_if(m_possibleTargetWarriors.begin(), 
            m_possibleTargetWarriors.end(), 
            std::mem_fn(&Warrior::isMarkedForRemoval));
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
    
    m_window.setView(m_guiView);
    m_guiEnvironment.update(dt);
    m_window.setView(m_gameView);
    if (m_playerWarrior)
    {
        m_healthBarWarr1->setProgress(m_playerWarrior->getCurrentHealth());
        m_stanimaBarWarr1->setProgress(m_playerWarrior->getCurrentStanima());
        //m_healthBarWarr1->setProgress((m_playerWarrior->getMaxHealth() / 100) 
        //        * m_playerWarrior->getCurrentHealth());
    }
    // If the container contains more then one warrior there is a enemy
    if (m_possibleTargetWarriors.size() > 1)
    {
        m_healthBarWarr2->setProgress(
                m_possibleTargetWarriors[1]->getCurrentHealth());
        m_stanimaBarWarr2->setProgress(
                m_possibleTargetWarriors[1]->getCurrentStanima());
    }
    return false;
}

void MainGameScreen::updateBackground(float dt)
{
    m_currentBgStepTime += dt;    
	float colPos{ m_currentBgStepTime / m_totalBgStepTime  };
	// Go next step when current step is completed
    if (m_currentBgStepTime > m_totalBgStepTime) 
	{
		colPos = 0.f;
		m_currentBgStepTime = 0.f;
		m_currentBgColorStep++;
		if (m_currentBgColorStep > m_bgColorSteps.size() - 1)
		{
			m_currentBgColorStep = 0;
		}
	}
	sf::Color curCol = Helpers::lerbRGBColor(
            m_bgColorSteps[m_currentBgColorStep][0], 
            m_bgColorSteps[m_currentBgColorStep][1], colPos);
    m_background.setFillColor(curCol);
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

void MainGameScreen::resolveEntityCollisions(SceneNode *sceneNodeFirst, 
        SceneNode *sceneNodeSecond, CollisionInfo &collisionInfo)
{
    Entity *entityOne{ static_cast<Entity*>(sceneNodeFirst) };
    Entity *entityTwo{ static_cast<Entity*>(sceneNodeSecond) };
    float overlap{ collisionInfo.getLength() };
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
        SceneNode *sceneNodeFirst{ collisionInfo.getCollidedFirst() };
        SceneNode *sceneNodeSecond{ collisionInfo.getCollidedSecond() };
        SceneNode::Pair sceneNodes{ collisionInfo.getCollidedFirst(), 
            collisionInfo.getCollidedSecond() };
        if (matchesCategories(sceneNodes, 
                    WorldObjectTypes::WARRIOR, WorldObjectTypes::WARRIOR))
        {
            resolveEntityCollisions(sceneNodeFirst, sceneNodeSecond, collisionInfo);
        }
        else if (matchesCategories(sceneNodes, 
                    WorldObjectTypes::WEAPON, WorldObjectTypes::WARRIOR))
        {
            Weapon *weapon{ static_cast<Weapon*>
                (getSceneNodeOfType(sceneNodes, WorldObjectTypes::WEAPON)) };
            Warrior *warrior{ static_cast<Warrior*>
                (getSceneNodeOfType(sceneNodes, WorldObjectTypes::WARRIOR)) };
            std::string warriorID{ warrior->getID() };
            // Only damage warrior if the weapon is not its own
            // Alternative implementation for future (?): no collision check with 
            // parent nodes
            if (warrior->getWeapon() != weapon && 
                    !weapon->wasIDAlreadyAttacked(warriorID))
            {
                warrior->handleDamage(weapon);
                // If the weapon was a projectile it should get destroyed after
                // colliding with warrior
                if (weapon->getType() & WorldObjectTypes::PROJECTILE)
                {
                    weapon->setStatus(WorldObjectStatus::DESTORYED);
                }
            }
        }
        /*
        else if (matchesCategories(sceneNodes, 
                    WorldObjectTypes::WEAPON, WorldObjectTypes::SHIELD))
        {
            std::cout << "Weapon Shield collision \n";
            Weapon *weapon{ static_cast<Weapon*>
                (getSceneNodeOfType(sceneNodes, WorldObjectTypes::WEAPON)) };
            Item *shield{ static_cast<Item*>
                (getSceneNodeOfType(sceneNodes, WorldObjectTypes::SHIELD)) };
            Warrior *warr{ static_cast<Warrior*> (shield->getParent()) };
            warr->setBlockedAttackID(weapon->getAttackID());
        }
        */
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

    //std::cout << "Cat1: " << category1 << " Cat2: " << category2 << " Type1: " 
    //<< type1 << " Type2: " << type2 << std::endl;
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
    if (m_isGamePaused && sf::Shader::isAvailable() && m_isRenderTextureAvailable)
    {
        // Draw first to a RenderTexture and then draw the RenderTexture whith the
        // black and white shader, so the shader is applied to shapes, too.
        m_renderTexture.clear();
        m_renderTexture.setView(m_gameView);
        m_renderTexture.draw(m_background);
        m_renderTexture.draw(m_renderManager);
        
        m_renderTexture.setView(m_guiView);
        m_renderTexture.draw(m_guiEnvironment);
        m_renderTexture.setView(m_gameView);
        
        m_renderTexture.display();
        const sf::Texture &texture{ m_renderTexture.getTexture() };
        sf::Sprite sprite(texture);
        m_window.setView(m_guiView);
        m_window.draw(sprite, &m_context.shaderHolder->get("grayscale"));
    }
    else
    {
        m_window.setView(m_gameView);
        m_window.draw(m_background);
        m_window.draw(m_renderManager);
        
        m_window.setView(m_guiView);
        m_window.draw(m_guiEnvironment);
    }
    m_window.setView(m_gameView);
}

void MainGameScreen::windowSizeChanged()
{
    calcGuiSizeAndPos();
    // Adjust size of RenderTexture
    if (!m_renderTexture.create(m_window.getSize().x, 
                m_window.getSize().y))
    {
        std::cout << "Error by creating RenderTexture \n";
        m_isRenderTextureAvailable = false;
    }
    else
    {
        m_isRenderTextureAvailable = true;
    }
}

void MainGameScreen::calcGuiSizeAndPos()
{
    // Health Bars
    m_healthBarWarr1->setBottomPosition(m_guiView.getSize().y - 10.f);
    m_healthBarWarr1->setLeftPosition(10.f);
    m_healthBarWarr2->setRightPosition(m_guiView.getSize().x - 10.f);
    m_healthBarWarr2->setBottomPosition(m_guiView.getSize().y - 10.f);
    // Stanima Bars
    m_stanimaBarWarr1->setLeftPosition(10.f);
    m_stanimaBarWarr1->setBottomPosition(m_guiView.getSize().y 
            - 10.f - m_healthBarWarr1->getLocalBounds().height - 10.f);
    m_stanimaBarWarr2->setRightPosition(m_guiView.getSize().x - 10.f);
    m_stanimaBarWarr2->setBottomPosition(m_guiView.getSize().y 
            - 10.f - m_healthBarWarr2->getLocalBounds().height - 10.f);
    // Console
    sf::Vector2f windowViewSize{ m_guiView.getSize() };
    m_consoleWidget->setWidth(windowViewSize.x - 
            2 * m_consoleWidget->getOutlineThickness());
    m_consoleWidget->setHeight(windowViewSize.y / 4);
    m_consoleWidget->setTopPosition(0.f);
    m_consoleWidget->setLeftPosition(0.f);
}
