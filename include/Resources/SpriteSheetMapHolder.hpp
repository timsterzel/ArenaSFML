#ifndef SPRITESHEETMAPHOLDER_HPP
#define SPRITESHEETMAPHOLDER_HPP
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include "Resources/EnumResourceIdentifiers.hpp"

class SpriteSheetMapHolder
{
    private:
        std::map<Textures, std::map<std::string, sf::IntRect> > m_resourceMap;

    public:
        void load(Textures id, const std::string &fileName);

        std::map<std::string, sf::IntRect> get(Textures id);

        sf::IntRect getRectData(Textures id, const std::string &identefier);

    private:
        //void loadRectData(const std::string &fileName);
        std::string getIdentifier(const std::string &line);
        sf::IntRect getIntRect(const std::string &line);
};


#endif // SPRITESHEETMAPHOLDER_HPP