#include "Resources/TileSetHolder.hpp"
#include <cassert>

void TileSetHolder::load(const std::string &fileName)
{
    tinyxml2::XMLDocument document;
    if (document.LoadFile(fileName.c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cout << "Error by loading tsx file. File path: " << fileName 
            << std::endl;
        return;
    }
    tinyxml2::XMLElement *tilesetEl{ document.FirstChildElement("tileset") };    
    if (!tilesetEl)
    {
        std::cout << "Error no tileset element in: " << fileName << std::endl;
        return;
    }
    
    
    const tinyxml2::XMLElement *properties{ 
        tilesetEl->FirstChildElement("properties")};
    if (!properties)
    {
        std::cout << "Error needed property is missing in: " << fileName 
            << std::endl;
        return;
    }
    const tinyxml2::XMLElement *property{ 
        tilesetEl->FirstChildElement("property")};
    if (!property)
    {
        std::cout << "Error needed property is missing in: " << fileName 
            << std::endl;
        return;
    }



    if (!(tilesetEl->Attribute("name") && 
        tilesetEl->Attribute("tilewidth") &&
        tilesetEl->Attribute("tileheight") && 
        tilesetEl->Attribute("tilecount") &&
        tilesetEl->Attribute("columns")))
    {
        std::cout << "Error needed attributes are missing in: " << fileName 
            << std::endl;
        return;
    }

    std::string name{ tilesetEl->Attribute("name") };
    float tileWidth{ std::stof(tilesetEl->Attribute("tilewidth")) };
    float tileHeight{ std::stof(tilesetEl->Attribute("tileheight")) };
    int tileCnt{ std::stoi(tilesetEl->Attribute("tilecount")) };
    int columns{ std::stoi(tilesetEl->Attribute("columns")) };

    const tinyxml2::XMLElement *imageEl{ tilesetEl->FirstChildElement("image") };
    

    //const tinyxml2::XMLElement *{ mapEl->FirstChildElement("tileset") }; a; 
    //        a = a->NextSiblingElement("tileset"))

    //for (const tinyxml2::XMLElement *a{ mapEl->FirstChildElement("tileset") }; a; 
    //        a = a->NextSiblingElement("tileset"))
    //rectMap.insert( { getIdentifier(line), getIntRect(line)});
    //m_resourceMap.insert( { id, rectMap } );
}


bool TileSetHolder::isTileSetExisting(const std::string &id) const
{
   return m_tileSets.find(id) != m_tileSets.end();
}

TileSet& TileSetHolder::getTileSet(const std::string &id) const
{
    assert(m_tileSets.find(id) != m_tileSets.end());
    return *m_tileSets.at(id);
}

TileSet& TileSetHolder::getTileSet(const std::string &id)
{
    assert(m_tileSets.find(id) != m_tileSets.end());
    return *m_tileSets.at(id);
}

