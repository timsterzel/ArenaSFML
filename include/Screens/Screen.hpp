#ifndef SCREEN_HPP
#define SCREEN_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include "Components/Warrior.hpp"
#include "Components/EnumWorldObjectTypes.hpp"
#include "Components/SceneNode.hpp"
#include "Render/RenderManager.hpp"
#include "Resources/ResourceHolder.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/SpriteSheetMapHolder.hpp"
#include "Input/QueueHelper.hpp"
#include "Input/Input.hpp"
#include "Input/Command.hpp"

class Game;

class Screen : private sf::NonCopyable
{
    protected:
        bool m_isInDebug;

        Game *m_game;
        sf::RenderWindow *m_window;

        SceneNode m_sceneGraph;
        RenderManager m_renderManager;

        const ResourceHolder<sf::Font, Fonts> &m_FontHolder;
        const ResourceHolder<sf::Texture, Textures> &m_TextureHolder;
        const SpriteSheetMapHolder &m_SpriteSheetMapHolder;

        QueueHelper<Input> *m_inputQueue;
        //QueueHelper<Command> m_commandQueue;

    public:
        Screen(const bool isInDebug, Game *game, sf::RenderWindow *window, const ResourceHolder<sf::Font, Fonts> &fontHolder,
                const ResourceHolder<sf::Texture, Textures> &textureHolder, const SpriteSheetMapHolder &spriteSheetMapHolder);

        virtual ~Screen();

        virtual void buildScene();

        virtual void handleInput(Input input, float dt);
        //void controlWorldEntities();
        //void handleCommands(float dt);
        virtual void update(float dt);

        virtual void render();

};

#endif // SCREEN_HPP
