#ifndef COLLISION_HPP
#define COLLISION_HPP
#include <SFML/Graphics.hpp>


class CollisionCircle;
class CollisionRect;

class Collision : public sf::Transformable, public sf::Drawable
{
    private:
        //SceneNode *m_parent;
    public:
        virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
        /*
        void setPosition(sf::Vector2f position);
        // The World position depends on the parent position (m_position is the relative position to the parents position)
        sf::Vector2f getWorldPosition();

        void setParent(SceneNode *parent);
        */

        // http://stackoverflow.com/questions/22899363/advice-on-class-structure-in-a-collision-detection-system (The accepted answer)
        virtual bool isColliding(const Collision &collider) const = 0;
        virtual bool isColliding(const CollisionCircle &collider) const = 0;
        virtual bool isColliding(const CollisionRect &collider) const = 0;
};

#endif // COLLISION_HPP
