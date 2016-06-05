#include "Input/Input.hpp"

Input::Input(InputTypes inputType)
: m_inputType{inputType}
{

}

Input::Input(InputTypes inputType, sf::Vector2f values)
: m_inputType{inputType}
, m_values{values}
{

}

InputTypes Input::getInputType() const
{
    return m_inputType;
}

void Input::setInputType(InputTypes inputType)
{
    m_inputType = inputType;
}

sf::Vector2f Input::getValues() const
{
    return m_values;
}

void Input::setValue(sf::Vector2f values)
{
    m_values = values;
}
