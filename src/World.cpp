#include "World.hpp"
#include "Components/SpriteNode.hpp"
#include "Components/Warrior.hpp"
#include "Calc.hpp"
#include <memory>


World::World(sf::RenderWindow *window, const ResourceHolder<sf::Font, Fonts> &fontHolder, const ResourceHolder<sf::Texture, Textures> &textureHolder
    /*,QueueHelper<Input> *inputQueue*/)
: m_window{window}
, m_worldView{m_window->getDefaultView()}
, m_fontHolder{fontHolder}
, m_textureHolder{textureHolder}
//, m_inputQueue{inputQueue}
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

    sf::Texture &texture = m_textureHolder.get(Textures::CHESS_WHITE);
    sf::IntRect textureRect(0.f, 0.f, 480, 800);
    texture.setRepeated(true);
    std::unique_ptr<SpriteNode> background(new SpriteNode(texture, textureRect));
    m_sceneLayers[Layers::BACKGROUND]->attachChild(std::move(background));


    std::unique_ptr<Warrior> warrior(new Warrior(Textures::KNIGHT, m_textureHolder));
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
        case InputTypes::TRANSLATED_CURSOR_POS:
            const sf::Vector2f UnitVecX(1.0, 0.f);
            // The angle which should be calculated have the coordinate systems midpoint at the center of the window,
            // so we have to use the translated mouse position so its relativ to the center of the window
            const sf::Vector2f TranslatedMousePos = { input.getValues() };
            const float Angle = { Calc::radToDeg(Calc::getVec2Angle<sf::Vector2f, sf::Vector2f>(UnitVecX, TranslatedMousePos)) };
            const float AngleSigned = TranslatedMousePos.y < 0.f ? -Angle : Angle;
            m_commandQueue.push({ CommandTypes::ROTATE, WorldObjectTypes::Player, { AngleSigned, 0.f } });
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

