#ifndef SCENENODE_HPP
#define SCENENODE_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <set>
#include "Collision/CollisionShape.hpp"
#include "Components/EnumWorldObjectTypes.hpp"
#include "Input/Command.hpp"

class SceneNode : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;
        typedef std::pair<SceneNode*, SceneNode*> Pair;

    private:
        std::vector<Ptr> m_children;
        SceneNode *m_parent;
    protected:
        std::unique_ptr<CollisionShape> m_collisionShape;
        WorldObjectTypes m_type;
        // A SceneNode is active it moves or rotate.
        // If it is only passive, so it dont move, rotate etc things can possibly collide with it (If it have a collision shape),
        // but a passive object can not do anything to collide with something. But Other SceneNodes can do things so they collides
        // with it. When we know that a SceneNode is passive we dont have to check collision twice. We just have to check if the
        // active SceneNode collides with the inActive SceneNode.
        // In a nutshell: When the SceneNode change his position or rotate its active.
        bool m_isActive;



        sf::Vector2f m_lastPos;
        float m_lastRot;
        sf::Vector2f m_lastScal;
    public:
        SceneNode();
        SceneNode(WorldObjectTypes type);
        void attachChild(Ptr child);
        Ptr detachChild(const SceneNode& node);

        void setCollisionShape(std::unique_ptr<CollisionShape> collisionShape);
        // dt is the delta time
        void update(float dt);
        void onCommand(const Command &command, float dt);
        // Get absolute world transform
        sf::Transform getWorldTransform() const;
        // Get absolute position in world
        sf::Vector2f getWorldPosition() const ;
        // Get absolute rotation in world
        float getWorldRotation() const;

        WorldObjectTypes getType() const;
        void setType(WorldObjectTypes type);

        CollisionShape* getCollisionShape() const;
        CollisionInfo isColliding(SceneNode &node) const;

        bool isActive() const;
        void setIsActive(bool isActive);

        // Check if the given SceneGraph and its child collides with the ScneGraph and its nodes
        void checkNodeCollision(SceneNode &node, std::set<Pair> &collisionPairs);
        void checkSceneCollision(SceneNode &sceneGraph, std::set<Pair> &collisionPairs);

        // Safe transform of the actual and parent nodes (position, rotation and scale)
        void safeTransform();
        // Safe the actual transform of the actual sceneNode and childs (position, rotation and scale)
        void safeChildTransform();
        // Safe the actual transform (position, rotation and scale)
        void safeCurrentTransform();
        // Restore the last state of position, rotation and scale (the pos and rotation of the entity before last change)
        void restoreLastTransform();

    private:
        // draw should not get overridden
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final;
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
        void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;
        virtual void updateCurrent(float dt);
        void updateChildren(float dt);
        virtual void onCommandCurrent(const Command &command, float dt);
        void onCommandChildren(const Command &command, float dt);
};

#endif // SCENENODE_HPP
