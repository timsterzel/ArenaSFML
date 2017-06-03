#ifndef ENUMINPUTTYPES_HPP
#define ENUMINPUTTYPES_HPP

/* Input Types get later ranslated to commands.
 * One Input can generate several commands.
 * How a InputType come about is platform depentend.
 * (Various platforms has different input options
 */

enum class InputTypes
{
    WINDOW_RESIZED,
    LOST_FOCUS,
    GAINED_FOCUS,
    MOUSE_POS,
    CURSOR_RIGHT_POS,
    CURSOR_LEFT_POS,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    ACTION_1,
    ACTION_2,
    SPECIAL_ACTION,
    ACTION_1_START,
    ACTION_1_STILL,
    ACTION_1_STOPPED,
    PAUSE,
    BACK,
    CONSOLE,
    
    // Debug
    D1,
    D2,
    D3,
    D4,
};

#endif // ENUMINPUTTYPES_HPP
