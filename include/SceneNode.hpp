#ifndef SCENENODE_HPP
#define SCENENODE_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Command.hpp"
#include "EnumWorldObjectTypes.hpp"

class SceneNode : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;

    private:
        std::vector<Ptr> m_children;
        SceneNode *m_parent;
    protected:
        WorldObjectType m_type;
    public:
        SceneNode();
        SceneNode(WorldObjectType type);
        void attachChild(Ptr child);
        Ptr detachChild(const SceneNode& node);
        // dt is the delta time
        void update(float dt);
        void onCommand(const Command &command, float dt);
        // Get absolute world transform
        sf::Transform getWorldTransform();
        // Get absolute world position
        sf::Vector2f getWorldPosition();

        WorldObjectType getType() const;
        void setType(WorldObjectType type);


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
