#include "TextureHolder.hpp"

TextureHolder::TextureHolder()
{

}

void TextureHolder::load(Textures id, const std::string &fileName)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture);
    texture->loadFromFile(fileName);

    m_textureMap.insert(std::make_pair(id, std::move(texture)));
}

sf::Texture& TextureHolder::get(Textures id)
{
    auto found = m_textureMap.find(id);
    return *found->second;
}

const sf::Texture& TextureHolder::get(Textures id) const
{
    auto found = m_textureMap.find(id);
    return *found->second;
}
