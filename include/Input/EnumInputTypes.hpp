#ifndef ENUMINPUTTYPES_HPP
#define ENUMINPUTTYPES_HPP

/* Input Types get later ranslated to commands.
 * One Input can generate several commands.
 * How a InputType come about is platform depentend.
 * (Various platforms has different input options
 */

enum class InputTypes
{
    TRANSLATED_CURSOR_POS,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

#endif // ENUMINPUTTYPES_HPP
