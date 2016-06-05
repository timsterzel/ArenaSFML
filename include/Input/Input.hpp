#ifndef INPUT_HPP
#define INPUT_HPP
#include <SFML/Graphics.hpp>
#include "Input/EnumInputTypes.hpp"

/* Stores a platform independet Input, which is later translated to a platform
 * indepentend command. A Input can result in different commands, depending on
 * actual screen and world
 */
class Input
{
    private:
        InputTypes m_inputType;
        sf::Vector2f m_values;

    public:
        Input(InputTypes inputType);
        Input(InputTypes inputType, sf::Vector2f values);

        InputTypes getInputType() const;
        void setInputType(InputTypes inputType);

        sf::Vector2f getValues() const;
        void setValue(sf::Vector2f values);
};

#endif // INPUT_HPP
