#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <memory>
#include <cassert>
#include "ResourceIdentifiers.hpp"

class TextureHolder
{
    private:
        std::map<Textures, std::unique_ptr<sf::Texture>> m_textureMap;

    public:
        TextureHolder();
        void load(Textures texture, const std::string &fileName);
        sf::Texture& get(Textures id);
        const sf::Texture& get(Textures id) const;


};

#endif // TEXTUREHOLDER_HPP
