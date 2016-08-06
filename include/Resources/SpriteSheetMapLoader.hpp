#ifndef SPRITESHEETMAPLOADER_HPP
#define SPRITESHEETMAPLOADER_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class SpriteSheetMapLoader
{
    public:
        static std::map<std::string, sf::IntRect> loadRectData(std::string fileName);

    private:
        static std::string getIdentifier(std::string line);
        static sf::IntRect getIntRect(std::string line);
};

#endif // SPRITESHEETMAPLOADER_HPP
