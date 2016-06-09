#include "World.hpp"
#include "Collision/CollisionShape.hpp"
#include "Collision/CollisionCircle.hpp"
#include "Collision/CollisionRect.hpp"
#include "Components/SpriteNode.hpp"
#include "Components/Warrior.hpp"
#include "Calc.hpp"
#include <memory>


World::World(sf::RenderWindow *window, const ResourceHolder<sf::Font, Fonts> &FontHolder, const ResourceHolder<sf::Texture, Textures> &TextureHolder
    /*,QueueHelper<Input> *inputQueue*/)
: m_window{window}
, m_worldView{m_window->getDefaultView()}
, m_FontHolder{FontHolder}
, m_TextureHolder{TextureHolder}
//, m_inputQueue{inputQueue}
, m_worldBounds{ 0.f, 0.f, 800.f, 480.f }
, m_playerWarrior{nullptr}
{

}

void World::buildScene()
{
    for (std::size_t i = { 0 }; i < Layers::COUNT; i++)
    {
        // Use std::unique_ptr<SceneNode>
        SceneNode::Ptr layer(new SceneNode());
        m_sceneLayers[i] = layer.get();
        m_sceneGraph.attachChild(std::move(layer));
    }

    sf::Texture &texture = m_TextureHolder.get(Textures::CHESS_WHITE);
    sf::IntRect textureRect(m_worldBounds);
    texture.setRepeated(true);
    std::unique_ptr<SpriteNode> background(new SpriteNode(texture, textureRect));
    m_sceneLayers[Layers::BACKGROUND]->attachChild(std::move(background));

    std::unique_ptr<Warrior> wizard(new Warrior(100, Textures::WIZARD, m_TextureHolder));
    std::unique_ptr<CollisionShape> collisionShapeWizard(new CollisionCircle(12.f));
    wizard->setCollisionShape(std::move(collisionShapeWizard));
    wizard->setPosition(800 / 2.f + 100.f, 480 / 2.f);
    wizard->setVelocity(30.f, 30.f);
    wizard->setType(WorldObjectTypes::ENEMY);
    m_sceneLayers[Layers::MAIN]->attachChild(std::move(wizard));


    std::unique_ptr<Warrior> warriorEnemy(new Warrior(100, Textures::KNIGHT, m_TextureHolder));
    std::unique_ptr<CollisionShape> collisionShapeWarriorEnemy(new CollisionRect({ 32.f, 32.f }));
    warriorEnemy->setCollisionShape(std::move(collisionShapeWarriorEnemy));
    warriorEnemy->setPosition(800 / 3.f + 100.f, 480 / 3.f);
    warriorEnemy->setVelocity(30.f, 30.f);
    warriorEnemy->setType(WorldObjectTypes::ENEMY);
    m_sceneLayers[Layers::MAIN]->attachChild(std::move(warriorEnemy));

    std::unique_ptr<Warrior> warrior(new Warrior(100, Textures::KNIGHT, m_TextureHolder));
    std::unique_ptr<CollisionShape> collisionShapeWarrior(new CollisionCircle(12.f));
    m_playerWarrior = warrior.get();
    m_playerWarrior->setCollisionShape(std::move(collisionShapeWarrior));
    m_playerWarrior->setPosition(800 / 2.f, 480 / 2.f);
    m_playerWarrior->setVelocity(60.f, 60.f);
    m_playerWarrior->setType(WorldObjectTypes::PLAYER);
    m_sceneLayers[Layers::MAIN]->attachChild(std::move(warrior));

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
    /*
    while(!m_commandQueue.isEmpty())
    {
        m_sceneGraph.onCommand(m_commandQueue.pop(), dt);
    }
    */
    m_sceneGraph.update(dt);
}

void World::render()
{
    //std::cout << "Render" << std::endl;
    //m_window->clear();
    m_window->draw(m_sceneGraph);
    //m_window->display();
}

