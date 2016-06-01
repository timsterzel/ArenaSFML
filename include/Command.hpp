#ifndef COMMAND_HPP
#define COMMAND_HPP

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
        Vector2f m_values;

    public:
        Command();

        CommandTypes getCommandType() const;
        void setCommandType(CommandTypes commandType);


};

#endif // COMMAND_HPP
