#ifndef MAINGAMESCREEN_HPP
#define MAINGAMESCREEN_HPP
#include "libs/GUI-SFML/include/GUI-SFML.hpp"
#include "Components/Warrior.hpp"
#include "Components/EnumWorldObjectTypes.hpp"
#include "Components/SceneNode.hpp"
#include "Input/QueueHelper.hpp"
#include "Input/Input.hpp"
#include "Input/Command.hpp"
#include "Render/RenderManager.hpp"
#include "Resources/ResourceHolder.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
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
        MainGameScreen(ScreenStack *screenStack, Context &context);

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
    private:
        SceneNode* getSceneNodeOfType(SceneNode::Pair sceneNodePair, WorldObjectTypes type);
        bool matchesCategories(SceneNode::Pair &colliders, unsigned int type1, unsigned int type2);
        void resolveEntityCollisions(SceneNode *sceneNodeFirst, SceneNode *sceneNodeSecond, CollisionInfo &collisionInfo);
        // Check if the player is still in game
        bool isStillPlayerIsInGame();
        void handleConsoleCommands(gsf::Widget* widget, sf::String command);

};

#endif // MAINGAMESCREEN_HPP
