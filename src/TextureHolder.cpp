#include "TextureHolder.hpp"

TextureHolder::TextureHolder()
{

}

void TextureHolder::load(Textures id, const std::string &fileName)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture);
    if (!texture->loadFromFile(fileName))
    {
        throw std::runtime_error("TextureHolder::load - Failed to load " + fileName);
    }
    auto inserted = m_textureMap.insert(std::make_pair(id, std::move(texture)));
    // Stop execute in debug mode when there was an error by inserting the resource(e.g try to add the same id twice)
    // Trying to load the same resource twice with the same id is a logical error so the progtam should stop immediately in debug mode
    assert(inserted.second);
}

sf::Texture& TextureHolder::get(Textures id)
{
    auto found = m_textureMap.find(id);
    // Stop programm in debug mode, when trying to get a resource which is not loaded
    assert(found != m_textureMap.end());
    return *found->second;
}

const sf::Texture& TextureHolder::get(Textures id) const
{
    auto found = m_textureMap.find(id);
    return *found->second;
}
