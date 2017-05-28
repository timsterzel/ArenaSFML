#include "Config/ConfigManager.hpp"
#include <iostream>
#include <fstream>
#include "Helpers.hpp"

ConfigManager::ConfigManager(const std::string &fileName)
{
    loadConfig(fileName);
}

bool ConfigManager::loadConfig(const std::string &fileName)
{
    m_configs.clear();
    std::ifstream file(fileName, std::ios_base::in);
    if (!file)
    {
        std::cerr << "Could not open file: " << fileName << std::endl;
        return false;
    }
    std::string line;
    while(std::getline(file, line))
    {
        // Ignore empty lines
        if (line.size() < 1) 
        {
            continue;
        }
        // Ignore headers
        if (line[0] == '[')
        {
            continue;
        }
        std::vector<std::string> configs{ Helpers::splitString(line, '=') };
        if (configs.size() < 2 || configs[0].size() == 0 || configs[1].size() == 0)
        {
            std::cerr << "Line: \"" << line << "\" is no valid configuration" 
                << std::endl;
            continue;
        }
        m_configs.insert(std::make_pair(configs[0], configs[1]));
    }
    return true;
}

bool ConfigManager::isKeyExisting(const std::string &key) const
{
    return m_configs.find(key) != m_configs.end();
}

std::string ConfigManager::getString(const std::string &key, 
        const std::string &defaultVal) const
{
    if (!isKeyExisting(key))
    {
        return defaultVal;
    }
    std::string val{ m_configs.at(key) };
    return val;
}

bool ConfigManager::getBool(const std::string &key, bool defaultVal) const
{
    if (!isKeyExisting(key))
    {
        return defaultVal;
    }
    std::string val{ m_configs.at(key) };
    if (val == "true")
    {
        return true;
    }
    if (val == "false")
    {
        return false;
    }
    std::cerr << "Value of key: \"" << key << "\" is no valid boolean."
        << " Invalid value is: " <<  val << std::endl;
    return defaultVal;
}

int ConfigManager::getInt(const std::string &key, int defaultVal) const
{
    if (!isKeyExisting(key))
    {
        return defaultVal;
    }
    std::string val{ m_configs.at(key) };
    int valNum{ defaultVal }; 
    try
    {
        std::stoi(val);        
    }
    catch(std::invalid_argument& e)
    {
        std::cerr << "Value of key: \"" << key << "\" is no valid int."
            << " Invalid value is: " <<  val << std::endl;
    }
    return valNum;
}


void ConfigManager::printConfig() const
{
    for (auto &pair : m_configs)
    {
        std::cout << "Key: \"" << pair.first << "\" value: \"" << pair.second 
            << std::endl;
    }
}
