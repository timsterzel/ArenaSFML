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
class ScreenStack;

class Screen : private sf::NonCopyable
{
    public:
        typedef std::unique_ptr<Screen> Ptr;

        struct Context
        {
            bool isInDebugMode;
            sf::RenderWindow *window;
            ResourceHolder<sf::Font, Fonts> *fontHolder;
            ResourceHolder<sf::Texture, Textures> *textureHolder;
            ResourceHolder<sf::Shader, Shaders> *shaderHolder;
            SpriteSheetMapHolder *spriteSheetMapHolder;
            MusicPlayer *music;

            Context(bool isInDebugMode, sf::RenderWindow *window, 
                    ResourceHolder<sf::Font, Fonts> *fontHolder,
                    ResourceHolder<sf::Texture, Textures> *textureHolder, 
                    ResourceHolder<sf::Shader, Shaders> *shaderHolder,
                    SpriteSheetMapHolder *spriteSheetMapHolder, MusicPlayer *music);
        };

    protected:

        Context &m_context;
        ScreenStack *m_screenStack;

        SceneNode m_sceneGraph;
        RenderManager m_renderManager;

        //QueueHelper<Input> *m_inputQueue;
        //QueueHelper<Command> m_commandQueue;

    public:
        Screen(ScreenStack *screenStack, Context &context);

        virtual ~Screen();

        virtual void buildScene();
        
        Context getContext();

        // return false when no lower screen should handle the input
        virtual bool handleInput(Input &input, float dt);
        virtual bool handleEvent(sf::Event &event, float dt);
        //void controlWorldEntities();
        //void handleCommands(float dt);
        virtual bool update(float dt);

        virtual void render();

};

#endif // SCREEN_HPP
