#include "Resources/LevelHolder.hpp"
#include <cassert>

void LevelHolder::load(const std::string &fileName, TileSetHolder &tileSetHolder)
{
    tinyxml2::XMLDocument document;
    if (document.LoadFile(fileName.c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cout << "Error by loading tmx file. File path: " << fileName 
            << std::endl;
        return;
    }
    tinyxml2::XMLElement *mapEl{ document.FirstChildElement("map") };
    std::string tileSetId;
    const tinyxml2::XMLElement *properties{ 
        mapEl->FirstChildElement("properties")};
    if (properties)
    {
        std::cout << "properties set\n";
        const tinyxml2::XMLElement *property{ 
            properties->FirstChildElement("property") };
        // Get tileset identifier (tmx_identifier)
        if (property && property->Attribute("value"))
        {
            tileSetId = property->Attribute("value");
        }
    }
        std::cout << "TileSetId: " << tileSetId << std::endl;
    /*
    for (const tinyxml2::XMLElement *a{ mapEl->FirstChildElement("tileset") }; a; 
            a = a->NextSiblingElement("tileset"))
    {
        std::cout << "TileSet Element\n";
        if (!a->Attribute("source"))
        {
            std::cerr << "No tileset specified \n";
        }
        else
        {
            std::string source = a->Attribute("source");
            if (!tileSetHolder.isTileSetExisting(source))
            {
                std::cout << "Tileset dont exists\n";
                tileSetHolder.load(source, source);
            }   
        }
        
    }
    */

}

std::vector<std::unique_ptr<Level>>& LevelHolder::getLevels()
{
    return m_levels;
}
