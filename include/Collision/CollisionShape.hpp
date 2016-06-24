#ifndef COLLISIONSHAPE_HPP
#define COLLISIONSHAPE_HPP
#include <SFML/Graphics.hpp>

class SceneNode;
class CollisionCircle;
class CollisionRect;

class CollisionShape : public sf::Transformable, public sf::Drawable
{
    protected:
        SceneNode *m_parent;
    public:
        CollisionShape();

        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

        // The World position depends on the parent position (the position is the relative position to the parents position)
        sf::Transform getWorldTransform() const;
        sf::Vector2f getWorldPosition() const;
        float getWorldRotation() const;
        void setParent(SceneNode *parent);

        // http://stackoverflow.com/questions/22899363/advice-on-class-structure-in-a-collision-detection-system (The accepted answer)
        virtual bool isColliding(CollisionShape &collider) = 0;
        virtual bool isColliding(CollisionCircle &collider) = 0;
        virtual bool isColliding(CollisionRect &collider) = 0;
};

#endif // COLLISIONSHAPE_HPP