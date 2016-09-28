#include "GUI/TextWidget.hpp"
#include <iostream>

TextWidget::TextWidget()
{

}

TextWidget::TextWidget(std::string text, sf::Font &font)
{
    init(text, font, 12, sf::Color::Black);
}

TextWidget::TextWidget(std::string text, sf::Font &font, int characterSize)
{
    init(text, font, characterSize, sf::Color::Black);
}

TextWidget::TextWidget(std::string text, sf::Font &font, int characterSize, sf::Color color)
{
    init(text, font, characterSize, color);
}

void TextWidget::init(std::string text, sf::Font &font, int characterSize, sf::Color color)
{
    m_text.setString(text);
    m_text.setFont(font);
	m_text.setCharacterSize(characterSize);
	m_text.setColor(color);
}

TextWidget::~TextWidget()
{

}

void TextWidget::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(m_text, states);
}

void TextWidget::updateCurrent(float dt)
{
    // Do nothing by default
}
