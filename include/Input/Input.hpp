#ifndef INPUT_HPP
#define INPUT_HPP
#include <SFML/Graphics.hpp>
#include "Input/EnumInputTypes.hpp"
#include "Input/EnumInputDevice.hpp"

/* Stores a input, which is later translated to a platform
 * indepentend command. A Input can result in different commands, depending on
 * actual screen and world
 */
class Input
{
    private:
        InputTypes m_inputType;
        InputDevice m_inputDevice;
        sf::Vector2f m_values;

    public:
        Input(InputTypes inputType, InputDevice inputDevice);
        Input(InputTypes inputType, InputDevice inputDevice, sf::Vector2f values);

        InputTypes getInputType() const;
        void setInputType(InputTypes inputType);
        
        InputDevice getInputDevice() const;
        void setInputDevice(InputDevice inputDevice);

        sf::Vector2f getValues() const;
        void setValue(sf::Vector2f values);
};

#endif // INPUT_HPP
