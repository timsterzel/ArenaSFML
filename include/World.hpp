#ifndef WORLD_HPP
#define WORLD_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include "Components/Warrior.hpp"
#include "Components/EnumWorldObjectTypes.hpp"
#include "Components/SceneNode.hpp"
#include "Resources/ResourceHolder.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Input/QueueHelper.hpp"
#include "Input/Input.hpp"
#include "Input/Command.hpp"


class World : private sf::NonCopyable
{
    private:
        // Use of enum instead of enum class, so we can use Layer as int
        enum Layers
        {
            BACKGROUND,
            MAIN,
            COUNT
        };

    private:
        sf::RenderWindow *m_window;
        sf::View m_worldView;

        SceneNode m_sceneGraph;
        std::array<SceneNode*, Layers::COUNT> m_sceneLayers;

        const ResourceHolder<sf::Font, Fonts> &m_fontHolder;
        const ResourceHolder<sf::Texture, Textures> &m_textureHolder;

        QueueHelper<Input> *m_inputQueue;
        QueueHelper<Command> m_commandQueue;

        Warrior *m_playerWarrior;

    public:
        World(sf::RenderWindow *window, const ResourceHolder<sf::Font, Fonts> &fontHolder,
                const ResourceHolder<sf::Texture, Textures> &textureHolder/*, QueueHelper<Input> *inputQueue*/);

        void buildScene();
        void translateInput(Input input, float dt);
        void handleCommands(float dt);
        void update(float dt);
        void render();

    private:

};

#endif // WORLD_HPP
