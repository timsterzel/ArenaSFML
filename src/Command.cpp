#include "Command.hpp"

Command::Command(CommandTypes commandType, WorldObjectType worldObjectType)
: m_commandType{commandType}
, m_worldObjectType{worldObjectType}
{

}

Command::Command(CommandTypes commandType, WorldObjectType worldObjectType, sf::Vector2f values)
: m_commandType{commandType}
, m_worldObjectType{worldObjectType}
, m_values{values}
{

}

CommandTypes Command::getCommandType() const
{
    return m_commandType;
}

void Command::setCommandType(CommandTypes commandType)
{
    m_commandType = commandType;
}

WorldObjectType Command::getWorldObjectType() const
{
    return m_worldObjectType;
}

void Command::setWorldObjectType(WorldObjectType worldObjectType)
{
    m_worldObjectType = worldObjectType;
}

sf::Vector2f Command::getValues() const
{
    return m_values;
}

void Command::setValue(sf::Vector2f values)
{
    m_values = values;
}
