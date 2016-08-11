#ifndef WORLD_HPP
#define WORLD_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include "Components/Warrior.hpp"
#include "Components/EnumWorldObjectTypes.hpp"
#include "Components/SceneNode.hpp"
#include "Resources/ResourceHolder.hpp"
#include "Resources/EnumResourceIdentifiers.hpp"
#include "Resources/SpriteSheetMapHolder.hpp"
#include "Input/QueueHelper.hpp"
#include "Input/Input.hpp"
#include "Input/Command.hpp"

class World : private sf::NonCopyable
{
    private:


    private:
        bool m_isInDebug;
        bool m_drawCollisionShape;

        sf::RenderWindow *m_window;
        sf::View m_worldView;

        SceneNode m_sceneGraph;
        //std::array<SceneNode*, Layers::COUNT> m_sceneLayers;

        const ResourceHolder<sf::Font, Fonts> &m_FontHolder;
        const ResourceHolder<sf::Texture, Textures> &m_TextureHolder;
        const SpriteSheetMapHolder &m_SpriteSheetMapHolder;

        QueueHelper<Input> *m_inputQueue;
        QueueHelper<Command> m_commandQueue;

        sf::FloatRect m_worldBounds;
        Warrior *m_playerWarrior;
        // TMP
        long colCnt = 0;

    public:
        World(const bool isInDebug, sf::RenderWindow *window, const ResourceHolder<sf::Font, Fonts> &fontHolder,
                const ResourceHolder<sf::Texture, Textures> &textureHolder, const SpriteSheetMapHolder &spriteSheetMapHolder);

        void buildScene();
        // Safe the actual position, rotation and scale of the SceneNode
        void safeSceneNodeTrasform();
        void translateInput(Input input, float dt);
        void controlWorldEntities();
        void handleCommands(float dt);
        void update(float dt);
        void resolveEntityCollisions(SceneNode *sceneNodeFirst, SceneNode *sceneNodeSecond, CollisionInfo &collisionInfo);
        void handleCollision(float dt);
        bool matchesCategories(SceneNode::Pair &colliders, WorldObjectTypes type1, WorldObjectTypes type2);
        void render();

};

#endif // WORLD_HPP
