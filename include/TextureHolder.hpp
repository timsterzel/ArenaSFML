#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
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


};

#endif // TEXTUREHOLDER_HPP
