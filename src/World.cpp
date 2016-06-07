#include "World.hpp"
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


    std::unique_ptr<Warrior> warrior(new Warrior(Textures::KNIGHT, m_TextureHolder));
    m_playerWarrior = warrior.get();
    m_playerWarrior->setPosition(800 / 2.f, 480 / 2.f);
    m_playerWarrior->setVelocity(30.f, 30.f);
    m_playerWarrior->setType(WorldObjectTypes::Player);
    m_sceneLayers[Layers::MAIN]->attachChild(std::move(warrior));

}

void World::translateInput(Input input, float dt)
{

    switch (input.getInputType())
    {
        case InputTypes::CURSOR_POS :
        {
            m_commandQueue.push({ CommandTypes::LOOK_AT, WorldObjectTypes::Player, input.getValues() });
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
            m_commandQueue.push({ CommandTypes::MOVE_UP, WorldObjectTypes::Player });
            break;
        case InputTypes::DOWN :
            m_commandQueue.push({ CommandTypes::MOVE_DOWN, WorldObjectTypes::Player });
            break;
        case InputTypes::LEFT :
            m_commandQueue.push({ CommandTypes::MOVE_LEFT, WorldObjectTypes::Player });
            break;
        case InputTypes::RIGHT :
            m_commandQueue.push({ CommandTypes::MOVE_RIGHT, WorldObjectTypes::Player });
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

