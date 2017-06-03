#ifndef MAINGAMESCREEN_HPP
#define MAINGAMESCREEN_HPP
#include "libs/GUI-SFML/include/GUI-SFML.hpp"
#include "Components/Warrior.hpp"
#include "Components/EnumWorldObjectTypes.hpp"
#include "Components/SceneNode.hpp"
#include "Input/QueueHelper.hpp"
#include "Input/Input.hpp"
#include "Input/Command.hpp"
#include "Level/Level.hpp"
#include "Render/RenderManager.hpp"
#include "Resources/ResourceHolder.hpp"
#include "Resources/SpriteSheetMapHolder.hpp"
#include "Screens/Screen.hpp"
#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

class MainGameScreen : public Screen
{
    private:
        bool m_isGamePaused;
        bool m_showCollisionInfo;
        
        sf::RenderWindow &m_window;
        const Level &m_level;
        // Stored which control device controls which player
        std::map<InputDevice, WorldObjectTypes> m_deviceMap;

        // Used to apply the shader right on all drawn things. Some shaders only
        // effects textures right, so when we want to use shaders, we first draw all
        // to the render texture and then draw the emerging tetxure with the shader
        sf::RenderTexture m_renderTexture;
        // Store if the creation of the renderTexture was successfully
        bool m_isRenderTextureAvailable;
        sf::View &m_gameView;
        sf::View &m_guiView;
        gsf::GUIEnvironment m_guiEnvironment;
        // The console widget is for debugging
        gsf::ConsoleWidget *m_consoleWidget;
        gsf::ProgressWidget *m_healthBarWarr1;
        gsf::ProgressWidget *m_healthBarWarr2;
        gsf::ProgressWidget *m_stanimaBarWarr1;
        gsf::ProgressWidget *m_stanimaBarWarr2;

        // Warriors which are in the game
        std::vector<Warrior*> m_possibleTargetWarriors;
           
        QueueHelper<Command> m_commandQueue;

        sf::FloatRect m_worldBounds;
        Warrior *m_playerWarrior;
        // TMP, Collision counter
        long colCnt = 0;

    public:
        MainGameScreen(ScreenStack *screenStack, Context &context, 
                const Level &level, const std::map<InputDevice, 
                WorldObjectTypes> deviceMap);

        virtual ~MainGameScreen();
        
        virtual void buildScene();
        // Safe the actual position, rotation and scale of the SceneNode
        void safeSceneNodeTrasform();
        virtual bool handleInput(Input &input, float dt) override;
        virtual bool handleEvent(sf::Event &event, float dt) override;
        //void controlWorldEntities();
        void handleCommands(float dt);
        virtual bool update(float dt);
    
        void handleCollision(float dt);

        virtual void render();
    
        virtual void windowSizeChanged();
    private:
        void buildLevel();

        SceneNode* getSceneNodeOfType(SceneNode::Pair sceneNodePair, 
                WorldObjectTypes type);
        bool matchesCategories(SceneNode::Pair &colliders, unsigned int type1, 
                unsigned int type2);
        void resolveEntityCollisions(SceneNode *sceneNodeFirst, 
                SceneNode *sceneNodeSecond, CollisionInfo &collisionInfo);
        // Check if the player is still in game
        bool isStillPlayerIsInGame();
        void handleConsoleCommands(gsf::Widget* widget, sf::String command);
        // Calculate the pos and the size of window size depending paramters of
        // gui environment
        void calcGuiSizeAndPos();
};

#endif // MAINGAMESCREEN_HPP
