#include "Resources/LevelHolder.hpp"
#include <cassert>
#include <fstream>
#include <sstream>
#include "Helpers.hpp"
#include "DebugHelpers.hpp"

void LevelHolder::load(const std::string &fileName)
{
    std::ifstream file(fileName, std::ios_base::in);
    if (!file)
    {
        std::cerr << "Could not open file: " << fileName << std::endl;
        return;
    }
    Settings settings;
    // First template type: the id which is used on the map
    // Second template type: the id which is used to identify the textures rect
    std::map<std::string, std::string> tileAliases;
    // First: id which is used on the map. Second:is collison on or off(true/false)
    std::map<std::string, bool> collisionInfo;
    std::unique_ptr<Level> level{ std::make_unique<Level>() };
    int currentMapRow{ 0 };
    int currentObjectRow{ 0 };
    std::string line;
    // Options are: "[settings]", "tile_aliases", "[map]", "[objects]"
    std::string actualOption;
    while(std::getline(file, line))
    {
        if (line.size() < 1) 
        {
            continue;
        }
        if (line[0] == '[')
        {
            actualOption = line;
            continue;
        }
        if (actualOption == "[settings]")
        {
            loadSettings(line, &settings);
        }
        else if(actualOption == "[tile_aliases]")
        {
            loadTileAliases(line, &tileAliases);
        }
        else if(actualOption == "[collision]")
        {
            loadCollision(line, &collisionInfo);
        }
        else if(actualOption == "[map]")
        {
            loadMap(line, settings, level.get(), tileAliases, collisionInfo, 
                    currentMapRow);
            currentMapRow++;
        }
        else if(actualOption == "[objects]")
        {
            loadObjects(line, settings, &(*level.get()), currentObjectRow);
            currentObjectRow++;
        }
    }
    file.close();
    level->name = settings.levelName;
    m_levels.push_back(std::move(level));
}

bool LevelHolder::loadSettings(const std::string &line, LevelHolder::Settings *settings)
{
    std::vector<std::string> setting{ 
        Helpers::splitString(line, ':') };
    if (setting.size() != 2)
    {
        std::cerr << "Line is no valid setting: \"" << line << "\"\n";
        return false;
    }
    std::string identifier{ setting[0] };
    std::string value{ setting[1] };
    if (identifier == "name")
    {
        settings->levelName = value;
    }
    else if (identifier == "tilewidth")
    {
        settings->tileWidth = std::stoi(value);
    }
    else if (identifier == "tileheight")
    {
        settings->tileHeight = std::stoi(value);
    }
    return true;
}

bool LevelHolder::loadTileAliases(const std::string &line, 
    std::map<std::string, std::string> *tileAliases)
{
    std::vector<std::string> alias{ 
        Helpers::splitString(line, ':') };
    if (alias.size() != 2)
    {
        std::cerr << "Line is no valid alias: \"" << line << "\"\n";
        return false;
    }
    tileAliases->insert(std::make_pair(alias[0], alias[1]));
    return true;
}

bool LevelHolder::loadCollision(const std::string &line, 
    std::map<std::string, bool> *collisionInfo)
{
    std::vector<std::string> alias{ 
        Helpers::splitString(line, ':') };
    if (alias.size() != 2)
    {
        std::cerr << "Line is no valid collison info: \"" << line << "\"\n";
        return false;
    }
    bool isCollisionOn{ alias[1] == "true" ? true : false };
    std::string id{ alias[0] };
    collisionInfo->insert(std::make_pair(id, isCollisionOn));
    return true;
}

bool LevelHolder::loadMap(const std::string &line, 
    const LevelHolder::Settings &settings, Level *level, 
    const std::map<std::string, std::string> &tileAliases,
    const std::map<std::string, bool> &collisionInfo,
    int currentRow)
{
    for (size_t column{ 0 }; column != line.size(); column++)
    {
        std::string tileIdStr;
        tileIdStr.push_back(line[column]);
        if (tileIdStr == "0")
        {
            // Empty tile 
            continue;
        }
        if (tileAliases.find(tileIdStr) == tileAliases.end())
        {
            std::cerr << "Char is no valid alias: \"" << tileIdStr << "\"\n";
            return false;
        }
        std::string id{ tileAliases.at(tileIdStr) };
        bool isCollisionOn{ false };
        // If there are collision info for this tile, load it
        auto colFound = collisionInfo.find(tileIdStr); 
        if (colFound != collisionInfo.end())
        {
            isCollisionOn = colFound->second;
        }
        int tileWidth{ settings.tileWidth };
        int tileHeight{ settings.tileHeight };
        sf::Vector2f pos = translateRowColumnToPosition(
                column, currentRow, tileWidth, tileHeight);
        Level::TileData tile{ id, pos , isCollisionOn };
        level->tiles.push_back(tile);
    }
    return true;
}

bool LevelHolder::loadObjects(const std::string &line, 
    const LevelHolder::Settings &settings, Level *level, int currentRow)
{
    for (size_t column{ 0 }; column != line.size(); column++)
    {
        std::string objIdStr;
        objIdStr.push_back(line[column]);
        int tileWidth{ settings.tileWidth };
        int tileHeight{ settings.tileHeight };
        sf::Vector2f pos = translateRowColumnToPosition(
                column, currentRow, tileWidth, tileHeight);
        if (objIdStr == "1")
        {
            level->spawnPoint1 = std::make_unique<Level::SpawnPoint>(1, pos);
        }
        else if (objIdStr == "2")
        {
            level->spawnPoint2 = std::make_unique<Level::SpawnPoint>(2, pos);
        }
        else if (objIdStr != "0")
        {
            std::cerr << "Char is no valid object: \"" << objIdStr << "\"\n";
            return false;
        }
    }
    return true;
}

std::vector<std::unique_ptr<Level>>& LevelHolder::getLevels()
{
    return m_levels;
}

sf::Vector2f LevelHolder::translateRowColumnToPosition(int column, int row,
    int tileWidth, int tileHeight)
{
    sf::Vector2f pos;
    pos.x = (tileWidth * column) + (tileWidth / 2.f);
    pos.y = (tileHeight * row) + (tileHeight / 2.f);
    return pos;    
}
