#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <SFML/Graphics.hpp>
#include "SceneNode.hpp"

enum class CommandTypes
{
    MOVE_LEFT,
    MOVE_RIGHT,
    MOVE_UP,
    MOVE_DOWN,
    NONE
};


class Command
{
    private:
        CommandTypes m_commandType;
        WorldObjectType m_worldObjectType;
        sf::Vector2f m_values;

    public:
        Command(CommandTypes commandType, WorldObjectType worldObjectType);
        Command(CommandTypes commandType, WorldObjectType worldObjectType, sf::Vector2f valuess);

        CommandTypes getCommandType() const;
        void setCommandType(CommandTypes commandType);

        WorldObjectType getWorldObjectType() const;
        void setWorldObjectType(WorldObjectType worldObjectType);

        sf::Vector2f getValues() const;
        void setValue(sf::Vector2f values);

};

#endif // COMMAND_HPP
