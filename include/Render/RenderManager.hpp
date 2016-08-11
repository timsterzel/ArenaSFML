#ifndef RENDERMANAGER_HPP
#define RENDERMANAGER_HPP
#include <SFML/Graphics.hpp>

class SceneNode;

// Manage that all SceneNodes of the given SceneGraph are drawn in the right order
class RenderManager : public sf::Drawable
{
    private:
        SceneNode *m_sceneGraph;

    public:
        RenderManager(SceneNode *sceneGraph);

        // draw should not get overridden
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const final;
};

#endif // RENDERMANAGER
