#ifndef MAINGAMESCREEN_HPP
#define MAINGAMESCREEN_HPP
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
        bool m_showCollisionInfo;

        // Warriors which are in the game
        std::vector<Warrior*> m_possibleTargetWarriors;

        QueueHelper<Command> m_commandQueue;

        sf::FloatRect m_worldBounds;
        Warrior *m_playerWarrior;
        // TMP, Collision counter
        long colCnt = 0;

    public:
        MainGameScreen(const bool isInDebug, sf::RenderWindow *window, const ResourceHolder<sf::Font, Fonts> &fontHolder,
                const ResourceHolder<sf::Texture, Textures> &textureHolder, const SpriteSheetMapHolder &spriteSheetMapHolder);

        virtual void buildScene();
        // Safe the actual position, rotation and scale of the SceneNode
        void safeSceneNodeTrasform();
        virtual void handleInput(Input input, float dt);
        //void controlWorldEntities();
        void handleCommands(float dt);
        virtual void update(float dt);

        void handleCollision(float dt);

        virtual void render();
    private:
        SceneNode* getSceneNodeOfType(SceneNode::Pair sceneNodePair, WorldObjectTypes type);
        bool matchesCategories(SceneNode::Pair &colliders, unsigned int type1, unsigned int type2);
        void resolveEntityCollisions(SceneNode *sceneNodeFirst, SceneNode *sceneNodeSecond, CollisionInfo &collisionInfo);
        // Check if the player is still in game
        bool isStillPlayerIsInGame();
};

#endif // MAINGAMESCREEN_HPP
