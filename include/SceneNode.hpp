#ifndef SCENENODE_HPP
#define SCENENODE_HPP
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>


class SceneNode : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
    public:
        typedef std::unique_ptr<SceneNode> Ptr;

    protected:
    private:
        std::vector<Ptr> m_children;
        SceneNode *m_parent;

    public:
        SceneNode();
        void attachChild(Ptr child);
        Ptr detachChild(const SceneNode& node);
        void update(float dt);
        // Get absolute world transform
        sf::Transform getWorldTransform();
        // Get absolute world position
        sf::Vector2f getWorldPosition();

    private:
        // draw should not get overridden
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final;
        virtual void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const;
        void drawChildren(sf::RenderTarget &target, sf::RenderStates states) const;
        virtual void updateCurrent(float dt);
        void updateChildren(float dt);
};

#endif // SCENENODE_HPP
