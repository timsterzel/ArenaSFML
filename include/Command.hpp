#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <SFML/Graphics.hpp>
#include "EnumWorldObjectTypes.hpp"

enum class CommandTypes
{
    ROTATE,
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
        WorldObjectTypes m_worldObjectType;
        sf::Vector2f m_values;

    public:
        Command(CommandTypes commandType, WorldObjectTypes worldObjectType);
        Command(CommandTypes commandType, WorldObjectTypes worldObjectType, sf::Vector2f valuess);

        CommandTypes getCommandType() const;
        void setCommandType(CommandTypes commandType);

        WorldObjectTypes getWorldObjectType() const;
        void setWorldObjectType(WorldObjectTypes worldObjectType);

        sf::Vector2f getValues() const;
        void setValue(sf::Vector2f values);

};

#endif // COMMAND_HPP
