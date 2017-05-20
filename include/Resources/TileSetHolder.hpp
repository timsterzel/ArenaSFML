#ifndef TILESETHOLDER_HPP
#define TILESETHOLDER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include "libs/GUI-SFML/libs/tinyxml2.h"

class TileSetHolder
{
    private:
        std::unique_ptr<sf::Texture> m_texture;
        std::map<std::string, sf::IntRect> m_rectMap;

    public:
        void load(const std::string &id, const std::string &fileName);

        sf::IntRect getRectData(const std::string &id) const;
        sf::IntRect getRectData(const std::string &id);
};


#endif // TILESETHOLDER_HPP
