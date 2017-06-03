#include "Input/Input.hpp"

Input::Input(InputTypes inputType)
: m_inputType{ inputType }
, m_inputDevice{ InputDevice::DEFAULT }
{

}

Input::Input(InputTypes inputType, InputDevice inputDevice)
: m_inputType{ inputType }
, m_inputDevice{ inputDevice }
{

}

Input::Input(InputTypes inputType, sf::Vector2f values)
: m_inputType{ inputType }
, m_inputDevice{ InputDevice::DEFAULT }
, m_values{ values }
{

}

Input::Input(InputTypes inputType, InputDevice inputDevice, sf::Vector2f values)
: m_inputType{ inputType }
, m_inputDevice{ inputDevice }
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

InputDevice Input::getInputDevice() const
{
    return m_inputDevice;
}
void Input::setInputDevice(InputDevice inputDevice)
{
    m_inputDevice = inputDevice;
}

sf::Vector2f Input::getValues() const
{
    return m_values;
}

void Input::setValue(sf::Vector2f values)
{
    m_values = values;
}
