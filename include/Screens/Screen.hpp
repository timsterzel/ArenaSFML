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


class MusicPlayer;

class Screen : private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<Screen> Ptr;

        struct Context
        {
            sf::RenderWindow *window;
            ResourceHolder<sf::Font, Fonts> *fontHolder;
            ResourceHolder<sf::Texture, Textures> *textureHolder;
            SpriteSheetMapHolder *spriteSheetMapHolder;
            MusicPlayer *music;

            Context(sf::RenderWindow *window, ResourceHolder<sf::Font, Fonts> *fontHolder, ResourceHolder<sf::Texture, Textures> *textureHolder,
            SpriteSheetMapHolder *spriteSheetMapHolder, MusicPlayer *music);
        };

    protected:
        bool m_isInDebug;

        Context m_context;

        SceneNode m_sceneGraph;
        RenderManager m_renderManager;

        //QueueHelper<Input> *m_inputQueue;
        //QueueHelper<Command> m_commandQueue;

    public:
        Screen(const bool isInDebug, Context context);

        virtual ~Screen();

        virtual void buildScene();

        virtual void handleInput(Input input, float dt);
        //void controlWorldEntities();
        //void handleCommands(float dt);
        virtual void update(float dt);

        virtual void render();

};

#endif // SCREEN_HPP
